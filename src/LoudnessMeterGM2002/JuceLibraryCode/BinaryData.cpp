/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== LICENSE ==================
static const unsigned char temp_binary_data_0[] =
"The MIT License\r\n"
"\r\n"
"Copyright (c) Carl Rogers, 2011\r\n"
"\r\n"
"Permission is hereby granted, free of charge, to any person obtaining a copy\r\n"
"of this software and associated documentation files (the \"Software\"), to deal\r\n"
"in the Software without restriction, including without limitation the rights\r\n"
"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\r\n"
"copies of the Software, and to permit persons to whom the Software is\r\n"
"furnished to do so, subject to the following conditions:\r\n"
"\r\n"
"The above copyright notice and this permission notice shall be included in\r\n"
"all copies or substantial portions of the Software.\r\n"
"\r\n"
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\r\n"
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\r\n"
"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\r\n"
"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\r\n"
"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\r\n"
"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\r\n"
"THE SOFTWARE.\r\n";

const char* LICENSE = (const char*) temp_binary_data_0;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x34bc1021:  numBytes = 1094; return LICENSE;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "LICENSE"
};

}
