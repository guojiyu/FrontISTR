/*
 ----------------------------------------------------------
|
| Software Name :HEC-MW Ver 4.0beta
|
|   ../src/FileReader.h
|
|                     Written by T.Takeda,    2011/06/01
|                                Y.Sato       2011/06/01
|                                K.Goto,      2010/01/12
|                                K.Matsubara, 2010/06/01
|
|   Contact address : IIS, The University of Tokyo CISS
|
 ----------------------------------------------------------
*/
#ifndef FILE_READER_HH_D67C7697_52EC_426c_A2D3_FB67B60AF90C
#define FILE_READER_HH_D67C7697_52EC_426c_A2D3_FB67B60AF90C
#include "CommonFile.h"
#include "TypeDef.h"
#include "MeshFactory.h"
#include "FileBlockName.h"
#include "Logger.h"
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include "ElementType.h"
#include "ElementProperty.h"
#include "FileReaderBinCheck.h"
#include <cctype> 
namespace FileIO{
class CFileReader{
public:
    CFileReader();
    virtual ~CFileReader();
private:
    string msLine;
protected:
    pmw::CMeshFactory *mpFactory;
    Utility::CLogger  *mpLogger;
    string& getLineSt(ifstream& ifs);
    string& getLine(ifstream& ifs);
    bool TagCheck(string& s_line, const char* ctag);
    uiint IntElemType(string& sElemType);
    uiint IntBndType(string& sBndType);
    void Split(const string& s, char c, vstring& v);
public:
    virtual void setFactory(pmw::CMeshFactory *pFactory);
    virtual bool Read(ifstream &ifs, string& sline)=0;
    virtual bool Read_bin(ifstream& ifs)=0;
protected:
    uiint getFileSize(ifstream& ifs);
    bool  Check_End(ifstream& ifs);
    bool  Check_IntSize(bool& b32, bool& bCheck, string& sClassName);
    bool  TagCheck_Bin(ifstream& ifs, bool bCheck, char cHead, const char *NameTag, const uiint& nLength);
    short Read_ElementType(ifstream& ifs, char* cElemName, short nLength, const char* cElemType, string& sElemName);
    void  Read_BndType(ifstream& ifs, string& sBndType);
    void  Read_AnyName(ifstream& ifs, string& sName);
};
}
#endif
