/*
 ----------------------------------------------------------
|
| Software Name :HEC-MW Ver 4.0beta
|
|   ../src/FileReaderContactMesh.h
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
#include "FileReader.h"
#include "boost/lexical_cast.hpp"
#include "ElementType.h"
#include "FileReaderBinCheck.h" 
namespace FileIO{
#ifndef _FILEREADERCONTACTMESH_H
#define	_FILEREADERCONTACTMESH_H
class CFileReaderContactMesh:public CFileReader{
public:
    CFileReaderContactMesh();
    virtual ~CFileReaderContactMesh();
    virtual bool Read(ifstream& ifs, string& sLine);
    virtual bool Read_bin(ifstream& ifs);
};
#endif	/* _FILEREADERCONTACTMESH_H */
}
