#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include "misc.h"
#include "parser.h"

namespace idogaf
{
Parser::Parser()
{
    //ctor
    silent_ = false;
}

Parser::Parser(const Parser& other)
{
    //copy ctor
    silent_ = other.silent_;
    document_ = other.document_;
}

Parser& Parser::operator=(const Parser& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    silent_ = rhs.silent_;
    document_ = rhs.document_;
    return *this;
}

//Getters
Document* Parser::GetDocument() { return &document_; }

//Setters
void Parser::Silent(bool silent) { silent_ = silent; }

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
    bool closingTag, emptyTag;
    std::string textBeforeTag;
    std::stack<Element*> eStack;
    Element* A;
    Element* B;
    A = ReadNextTag(stream, emptyTag, closingTag, textBeforeTag);
    if(A == nullptr) return !stream.fail();
    else if(emptyTag || closingTag)
    {
        if(!silent_)
        {
            std::cerr << "Unexpected tag " << A->GetName() << std::endl;
            std::cerr << "Document is probably ill formed.\n";
        }
        return false;
    }
    while(true)
    {
        B = ReadNextTag(stream, emptyTag, closingTag, textBeforeTag);
        if(B == nullptr) return !stream.fail();
        else if(emptyTag)
            A->AddChild(B);
        else if(closingTag)
        {
            if(A->GetName() == B->GetName())
            {
                A = eStack.top();
                eStack.pop();
            }
            else
            {
                Element* C;
                do{
                    C = eStack.top();
                    eStack.pop();
                    if(eStack.empty() && C->GetName() != B->GetName())
                        return false;
                    else if(eStack.empty()) return true;
                } while(C->GetName() != B->GetName());
                A = eStack.top();
                eStack.pop();
            }
        }
        else
        {
            A->AddChild(B);
            eStack.push(A);
            B = A;
        }
    }
}

//Protected member functions
Element* Parser::ReadNextTag(std::istream& stream, bool& emptyOut,
                             bool& closeOut, std::string& textOut)
{
    emptyOut = false;
    closeOut = false;
    textOut = "";
    std::string activeBuffer;
    Element* ret = new Element();
    std::stringbuf buffer;

    while(stream.good())
    {
        activeBuffer = "";
        buffer.str("");
        while(stream.peek() != '<')
        {
            stream.get(buffer, '<');
            if(stream.peek() == '\n') buffer.sputc('\n');
            while(stream.peek() == '\n') { stream.get(); }
        }
        textOut += trim(buffer.str());
        //here in next char in stream is '<' (next tag ready to extract)
        //and in textOut we have any text (nicely trimmed) between
        //the stream cursor at the moment this func was called
        //and the next tag

        buffer.str("");
        while(stream.peek() != '>')
        {
            stream.get(buffer, '>');
            if(stream.peek() == '\n') buffer.sputc(' ');
            while(stream.peek() == '\n') { stream.get(); }
        }
        buffer.sputc(stream.get());   //extract '>' into buffer
        activeBuffer = buffer.str();

        if(activeBuffer.substr(0,4) == "<!--")  //Comment tag
        {   //Ignore comments for now
            //Just add new line to the text
            textOut += '\n';
        }
        else if(activeBuffer.substr(0,9) == "<!DOCTYPE")
        {
            //Extract anything between '<!DOCTYPE' and '>'
            activeBuffer = activeBuffer.substr(8, activeBuffer.length()-8-1);
            document_.SetDoctype(trim(activeBuffer));   //Set Doctype
            textOut += '\n';
        }
        else if(activeBuffer.substr(0,2) == "</")   //Closing tag
        {
            closeOut = true;
            //Extract anything between '</' and '>'
            activeBuffer = activeBuffer.substr(2, activeBuffer.length()-2-1);
            ret->SetName(trim(activeBuffer));
            return ret;
        }
        else if(activeBuffer.substr(activeBuffer.length()-2,2) == "/>") //
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
            return ParseTagForElement(activeBuffer);
        }
    }
    return nullptr;
}

Element* Parser::ParseTagForElement(const std::string& tag)
{
    std::stringstream sstream(tag);
    std::string buffer;
    try{
        sstream >> buffer;
    } catch(const std::ios_base::failure& e)
    {
        if(!silent_)
        {
            std::cerr   << "ios_base::failure exception caught while parsing a tag.\n"
                        << "Error code: " << e.code() << '\n';
        }
        return nullptr;
    }
    Element* ret = new Element(buffer);  //construct with name
    while(sstream.good())
    {
        sstream >> buffer;
        ret->AddAtrribute(ParseStringForAttribute(buffer));
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

}
