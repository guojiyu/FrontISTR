/*
 ----------------------------------------------------------
|
| Software Name :HEC-MW Ver 4.0beta
|
|   ../src/Solver.h
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
#ifndef SOLVER_H_
#define SOLVER_H_
#include "TypeDef.h"
namespace pmw
{
class CAssyMatrix;
class CAssyVector;
class CSolver
{
public:
	CSolver(iint iter_max, double tolerance,
			iint method, iint precondition,
			bool flag_iter, bool flag_time);
	virtual ~CSolver();
	void setFlagNewMesh(bool flag_new);
	void setFlagNewCoef(bool flag_new);
	void setIterMax(iint iter_new);
	iint getIterMax();
	void setTolerance(double tol_new);
	double getTolerance();
	void setMethod(uiint method);
	uiint getMethod();
	void setPrecondition(iint precondition);
	iint getPrecondition();
	void setFlagIterLog(bool flag_new);
	bool getFlagIterLog();
	void setFlagTimeLog(bool flag_new);
	bool getFlagTimeLog();
	uiint solve(const CAssyMatrix *pA, const CAssyVector *pB, CAssyVector *pX);
private:
	virtual uiint doSolve(const CAssyMatrix *pA, const CAssyVector *pB, CAssyVector *pX,
			iint iter_max, double tolerance,
			bool flag_iter_log, bool flag_time_log) = 0;
	iint mIterMax;
	double mTolerance;
	iint mMethod;
	iint mPrecondition;
	bool mFlagIterLog;
	bool mFlagTimeLog;
	bool mFlagNewMesh;
	bool mFlagNewCoef;
};
}
#endif /* SOLVER_H_ */
