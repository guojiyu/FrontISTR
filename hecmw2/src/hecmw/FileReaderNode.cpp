/*
 ----------------------------------------------------------
|
| Software Name :HEC-MW Ver 4.0beta
|
|   ../src/FileReaderNode.cpp
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
#include "FileReaderNode.h"
using namespace FileIO;
CFileReaderNode::CFileReaderNode()
{
}
CFileReaderNode::~CFileReaderNode()
{
}
bool CFileReaderNode::Read(ifstream& ifs, string& sLine)
{
    uiint   nNodeID, nMeshID, numOfNode, maxID, minID;
    vdouble vCoord; vCoord.resize(3);
    uiint  nType, nNumOfScalarDOF, nNumOfVectorDOF;
    string sType;
    uiint  mgLevel(0); 
    if(TagCheck(sLine, FileBlockName::StartNode()) ){
        sLine = getLineSt(ifs);
        istringstream iss(sLine.c_str());
        iss >> numOfNode >> nMeshID >> maxID >> minID;
        mpFactory->reserveNode(mgLevel, nMeshID, numOfNode);
        mpFactory->initBucketNode(mgLevel, nMeshID, maxID, minID);
        uiint nCount(0);
        while(!ifs.eof()){
            sLine = getLineSt(ifs);
            if(TagCheck(sLine, FileBlockName::EndNode()) ) break;
            istringstream iss(sLine.c_str());
            iss  >> sType >> nNumOfScalarDOF >> nNumOfVectorDOF >> nNodeID >> vCoord[0] >> vCoord[1] >> vCoord[2];
            if(sType=="sv"||sType=="SV"){
                nType=pmw::NodeType::ScalarVector;
            }else if(sType=="s"||sType=="S"){
                nType=pmw::NodeType::Scalar;
            }else if(sType=="v"||sType=="V"){
                nType=pmw::NodeType::Vector;
            }
            else{
                mpLogger->Info(Utility::LoggerMode::Error,"NodeType mismatch, at FileReaderNode");
            }
            if(!mpFactory) mpLogger->Info(Utility::LoggerMode::MWDebug, "Factory => NULL, at FileReaderNode");
            mpFactory->GeneNode(mgLevel, nMeshID, nNodeID, vCoord, nType, nNumOfScalarDOF, nNumOfVectorDOF);
            mpFactory->setIDBucketNode(mgLevel, nMeshID, nNodeID, nCount);
            nCount++;
        };
        mpFactory->setupNode(mgLevel, nMeshID);
        mpFactory->resizeAggregate(mgLevel, nMeshID, nCount);
        mpFactory->GeneAggregate(mgLevel, nMeshID, nCount);  
        return true;
    }else{
        return false;
    }
}
bool CFileReaderNode::Read_bin(ifstream& ifs)
{
    return true;
}
