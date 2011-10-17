/*
 ----------------------------------------------------------
|
| Software Name :HEC-MW Ver 4.0beta
|
|   ../src/FileReaderElementGroupEntity.cpp
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
#include "HEC_MPI.h"
#include "FileReaderElementGroupEntity.h"
using namespace FileIO;
using namespace boost;
CFileReaderElementGroupEntity::CFileReaderElementGroupEntity()
{
    ;
}
CFileReaderElementGroupEntity::~CFileReaderElementGroupEntity()
{
    ;
}
bool CFileReaderElementGroupEntity::Read(ifstream& ifs, string& sLine)
{
    uiint nGrpID;
    uiint nElemID, nMeshID;
    vuint vElemID;
    if(TagCheck(sLine, FileBlockName::StartElementGroupEntity()) ){
        cout << "ElementGroupEntity:Block Name : " << sLine << endl;
        uiint nCount(0);
        while(!ifs.eof()){
            sLine = getLine(ifs);
            if(TagCheck(sLine, FileBlockName::EndElementGroupEntity()) ) break;
            if(nCount==0){
                istringstream iss(sLine.c_str());
                iss >> nGrpID >> nMeshID;
            }else{
                char_separator<char> sep(" \t\n");
                tokenizer< char_separator<char> > tokens(sLine, sep);
                typedef tokenizer< char_separator<char> >::iterator Iter;
                for(Iter it=tokens.begin(); it != tokens.end(); ++it){
                    string str = *it;
                    nElemID = atoi(str.c_str());
                    vElemID.push_back(nElemID);
                    cout << " ElemID:" << nElemID;
                };
                cout << endl;
            }
            nCount++;
        };
        mpFactory->setElemID_with_ElemGrp(0, nMeshID, nGrpID, vElemID);
        return true;
    }else{
        return false;
    }
}
bool CFileReaderElementGroupEntity::Read_bin(ifstream& ifs)
{
    return true;
}
