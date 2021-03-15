#include "parser.h"

#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

#include "misc.h"

namespace idogaf
{

Parser::Parser()
{
    silent_ = false;
    skipUnnecessaryClosingTags_ = false;
    allowMistypedCommentTags_ = false;
}

Parser::Parser(const Parser& other)
{
    silent_ = other.silent_;
    document_ = other.document_;
    skipUnnecessaryClosingTags_ = other.skipUnnecessaryClosingTags_;
    allowMistypedCommentTags_ = other.allowMistypedCommentTags_;
}

Parser& Parser::operator=(const Parser& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    silent_ = rhs.silent_;
    document_ = rhs.document_;
    skipUnnecessaryClosingTags_ = rhs.skipUnnecessaryClosingTags_;
    allowMistypedCommentTags_ = rhs.allowMistypedCommentTags_;
    return *this;
}

//Getters
Document Parser::GetDocument() const
{
    return document_;
}
Document* Parser::GetDocumentPtr()
{
    return &document_;
}
bool Parser::Silent() const
{
    return silent_;
}
bool Parser::SkipUnnecessaryClosingTags() const
{
    return skipUnnecessaryClosingTags_;
}
bool Parser::AllowMistypedCommentTags() const
{
    return allowMistypedCommentTags_;
}

//Setters
void Parser::Silent(bool silent)
{
    silent_ = silent;
}
void Parser::SkipUnnecessaryClosingTags(bool value)
{
    skipUnnecessaryClosingTags_ = value;
}
void Parser::AllowMistypedCommentTags(bool value)
{
    allowMistypedCommentTags_ = value;
}

//Other
bool Parser::Parse(const std::string& filename)
{
    std::ifstream stream;
    stream.open(filename, std::ios::in | std::ios::binary);
    if(!stream.good())
    {
        if(!silent_)
            std::cerr << "Error opening file " << filename << std::endl;
        return false;
    }
    bool ret = Parse(stream);
    stream.close();
    return ret;
}

bool Parser::Parse(std::istream& stream)
{
    size_t lineCounter = 1;
    size_t linesOut = 0;
    bool closingTag, emptyTag;
    std::string textBeforeTag;
    std::stack<Element*> eStack;
    Element root;
    Element* A;
    Element B;
    root = ReadNextTag(stream, emptyTag, closingTag, textBeforeTag, linesOut);
    lineCounter += linesOut;
    if(root.Empty()) return !stream.fail();
    else if(emptyTag || closingTag)
    {
        return UnexpectedTagError(root.GetName(), lineCounter);
    }
    document_.SetRoot(root);
    A = document_.GetRootPtr();
    while(true)
    {
        B = ReadNextTag(stream, emptyTag, closingTag, textBeforeTag, linesOut);
        lineCounter += linesOut;
        if(!textBeforeTag.empty()) A->AddText(textBeforeTag);
        if(B.Empty()) return !stream.fail();
        else if(emptyTag)
            A->AddChild(B);
        else if(closingTag)
        {
            if(A->GetName() == B.GetName())
            {
                if(eStack.empty()) return true;
                A = eStack.top();
                eStack.pop();
            }
            else
            {
                if(!eStack.empty())
                {
                    if(omittClosingTagNMC(A->GetName(), eStack.top()->GetName())
                        && trim(textBeforeTag).empty()
                        && eStack.top()->GetName() == B.GetName())
                    {
                        eStack.pop();
                        if(eStack.empty()) return true;
                        A = eStack.top();
                        eStack.pop();
                        continue;
                    }
                }
                if(skipUnnecessaryClosingTags_) continue;
                return UnexpectedTagError(B.GetName(), lineCounter);
            }
        }
        else if(omittClosingTag(A->GetName(), B.GetName())
                && trim(textBeforeTag).empty())
        {
            eStack.top()->AddChild(B);
            A = eStack.top()->GetLastChildPtr();
        }
        else
        {
            A->AddChild(B);
            eStack.push(A);
            A = A->GetLastChildPtr();
        }
    }
}

bool Parser::WriteToFile(const std::string& filename)
{
    std::ofstream file;
    file.open(filename);
    bool ret = WriteToStream(file);
    file.close();
    return ret;
}

bool Parser::WriteToStream(std::ostream& stream)
{
    if(document_.Empty()) return DocumentEmptyError();
    //Create copy of the root so, we can use pointers during writing
    //without caring if someone modifies it during our work,
    //posibly invalidating our pointers.
    Element root = document_.GetRoot();
    Element* current = &root;

    //Print doctype if exists
    if(!document_.GetDoctype().empty())
        stream << "<!DOCTYPE " << document_.GetDoctype() << ">\n";
    if(root.Empty()) return true;

    std::stack<unsigned int> uiStack;
    unsigned int curSiblingPos = 0;
    unsigned int indent = 0;
    bool running = true;
    while(running)
    {
        WriteOpeningTag(current, stream, indent);

        if(current->GetChildrenCount() > 0)
        {
            uiStack.push(curSiblingPos);
            current = current->GetFirstChildPtr();
            curSiblingPos = 0;
            indent++;
        }
        else
        {
            while(true)
            {
                if(current->GetParent() == nullptr)
                {
                    WriteClosingTag(current, stream, indent);
                    running = false;
                    break;
                }
                else if(current->GetParent()->GetChildrenCount() > ++curSiblingPos)
                {
                    current = current->GetParent()->GetChildPtrAt(curSiblingPos);
                    break;
                }
                else
                {
                    current = current->GetParent();
                    curSiblingPos = uiStack.top();
                    uiStack.pop();
                    indent--;
                    WriteClosingTag(current, stream, indent);
                }
            }
        }
    }
    return true;
}

//Protected member functions
Element Parser::ReadNextTag(std::istream& stream, bool& emptyOut,
                            bool& closeOut, std::string& textOut,
                            size_t& linesOut)
{
    emptyOut = false;
    closeOut = false;
    textOut = std::string();
    linesOut = 0;
    std::string activeBuffer;
    Element ret = Element();
    std::stringbuf buffer;

    while(stream.good())
    {
        activeBuffer = "";
        buffer.str("");
        while(stream.peek() != '<')
        {
            stream.get(buffer, '<');
        }
        linesOut += countLines(buffer.str());
        textOut += trim(buffer.str());
        //Here in next char in stream is '<' (next tag ready to extract).
        //Iin textOut we have any text (nicely trimmed) between
        //the stream cursor at the moment this func was called
        //and the next tag

        buffer.str("");
        while(stream.peek() != '>')
        {
            stream.get(buffer, '>');
        }
        linesOut += countLines(buffer.str());
        buffer.sputc(stream.get());   //extract '>' into buffer
        activeBuffer = buffer.str();

        if(activeBuffer.substr(0,4) == "<!--"           //Comment tag
           || (activeBuffer.substr(0,5) == "<! --"
               && allowMistypedCommentTags_))           //Mistyped comment tag
        {
            //Ignore comments for now
            //Just add new line to the text
            textOut += '\n';
            if(activeBuffer.substr(activeBuffer.length()-3,3) != "-->")
            {
                buffer.str("");
                while(stream.good())
                {
                    stream.get(buffer, '>');
                    buffer.sputc(stream.get());
                    activeBuffer = buffer.str();
                    if(activeBuffer.substr(activeBuffer.length()-3,3) == "-->")
                        break;
                }
                linesOut += countLines(buffer.str());
            }
        }
        else if(activeBuffer.substr(0,9) == "<!DOCTYPE")
        {
            //Extract anything between '<!DOCTYPE' and '>'
            activeBuffer = activeBuffer.substr(9, activeBuffer.length()-9-1);
            document_.SetDoctype(trim(activeBuffer));   //Set Doctype
            textOut += '\n';
        }
        else if(activeBuffer.substr(0,7) == "<script")
        {
            //Extract anything between '<' and '>'
            activeBuffer = activeBuffer.substr(1, activeBuffer.length()-1-1);
            if(activeBuffer[activeBuffer.length()-1] == '/') //empty script tag
            {
                emptyOut = true;
                activeBuffer = activeBuffer.substr(0,activeBuffer.length()-1);
                return ParseTagForElement(activeBuffer);
            }
            //Since script tag can't have children, we extract text
            //and return element as empty but with text included
            ret = ParseTagForElement(activeBuffer);
            activeBuffer = "";
            buffer.str("");
            while(stream.good())
            {
                if(stream.peek() != '<')
                    stream.get(buffer, '<');
                if(stream.peek() == '\n')
                {
                    linesOut++;
                    buffer.sputc('\n');
                    stream.get();
                    continue;
                }
                std::string buf = " ";
                for(int i = 1; i < 15 && buf[i-1] != '>' && stream.good(); i++)
                    buf += static_cast<char>(stream.get());
                if(trim(buf.substr(3,buf.length()-3-1)) == "script") break;
                else buffer.sputn(buf.c_str(),buf.length());
            }
            linesOut += countLines(buffer.str());
            ret.AddText(trim(buffer.str()));
            emptyOut = true;
            return ret;
        }
        else if(activeBuffer.substr(0,2) == "</")   //Closing tag
        {
            closeOut = true;
            //Extract anything between '</' and '>'
            activeBuffer = activeBuffer.substr(2, activeBuffer.length()-2-1);
            ret.SetName(trim(activeBuffer));
            return ret;
        }
        else if(activeBuffer.substr(activeBuffer.length()-2,2) == "/>") //empty tag
        {
            emptyOut = true;
            //Extract anything between '<' and '/>'
            activeBuffer = activeBuffer.substr(1, activeBuffer.length()-2-1);
            //Parse active buffer for name and attributes
            return ParseTagForElement(activeBuffer);
        }
        else    //Opening tag
        {
            //Extract anything between '<' and '>'
            activeBuffer = activeBuffer.substr(1, activeBuffer.length()-1-1);
            //Parse active buffer for name and attributes
            ret = ParseTagForElement(activeBuffer);
            if(strInVector(ret.GetName(), kSingletonTags))
                emptyOut = true;
            break;
        }
    }
    return ret;
}

Element Parser::ParseTagForElement(const std::string& tag)
{
    std::stringstream sstream(tag);
    std::string buffer;
    try
    {
        sstream >> buffer;
    }
    catch(const std::ios_base::failure& e)
    {
        if(!silent_)
        {
            std::cerr   << "ios_base::failure exception caught while parsing a tag.\n"
                        << "Error code: " << e.code() << '\n';
        }
        return Element();
    }
    Element ret = Element(buffer);  //construct with name
    while(sstream.good())
    {
        sstream >> buffer;
        while(sstream.good() && buffer[buffer.length()-1] != '"')
        {
            //handle artibutes with spaces in value
            std::string buffer2;
            sstream >> buffer2;
            buffer += ' ';
            buffer += buffer2;
        }
        ret.AddAtrribute(ParseStringForAttribute(buffer));
    }
    return ret;
}

Attribute Parser::ParseStringForAttribute(const std::string& str)
{
    size_t eqPos = str.find('=');
    if(eqPos == std::string::npos) return Attribute(str);
    //Assuming format name="value"
    std::string name = str.substr(0, eqPos);
    std::string value = str.substr(eqPos+2,str.length()-eqPos-2-1);
    return Attribute(name, value);
}

void Parser::WriteOpeningTag(Element* element, std::ostream& stream,
                             unsigned int indent)
{
    if(element == nullptr) return;

    stream << GetIndentation(indent) << '<' << element->GetName();

    Vector_A attributes = element->GetAttributes();

    for(Vector_A_it it = attributes.begin(); it != attributes.end(); ++it)
        stream << ' ' << it->GetName() << "=\"" << it->GetValue() << "\"";
    if(element->GetChildrenCount() == 0 && element->GetText().empty()
            && element->GetName() != "meta" && element->GetName() != "link"
            && element->GetName() != "script")
        stream << "/>\n";
    else if(element->GetChildrenCount() == 0 && !element->GetText().empty())
    {
        stream << ">\n" << GetIndentation(indent+1);
        std::string text = element->GetText();
        for(size_t i = 0; i < text.length(); i++)
        {
            stream << text[i];
            if(text[i] == '\n') stream << GetIndentation(indent+1);
        }
        stream << '\n';
        WriteClosingTag(element, stream, indent);
    }
    else if(element->GetName() == "script")
    {
        stream << '>';
        WriteClosingTag(element, stream, 0);
    }
    else
        stream << ">\n";
}

void Parser::WriteClosingTag(Element* element, std::ostream& stream,
                             unsigned int indent)
{
    if(element == nullptr) return;

    stream << GetIndentation(indent) << "</" << element->GetName() << ">\n";
}

std::string Parser::GetIndentation(unsigned int level) const
{
    if(level == 0) return "";
    std::string indentation;
    for(unsigned int i = 0; i < level; i++)
        indentation += '\t';
    return indentation;
}

bool Parser::UnexpectedTagError(const std::string& tagName, size_t line) const
{
    if(!silent_)
    {
        std::cerr << "Error: Unexpected tag " << tagName;
        std::cerr << " at line " << line << std::endl;
        std::cerr << "Document is probably ill formed.\n";
    }
    return false;
}

bool Parser::DocumentEmptyError() const
{
    if(!silent_)
        std::cerr << "Error: Document is empty." << std::endl;
    return false;
}

}
