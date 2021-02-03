/***************************************************************
 * Copyright (C) 1992-2003
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TSGRAPH.H
 * PURPOSE     : Tough Space (3D) Graphics handle function
 *               implementation.
 *               Base types, macros and functions headers.
 * PROGRAMMER  : Vitaly A.Galinsky & Eugeny Zhidkov.
 * LAST UPDATE : 16.12.2003 (from 14.01.1999)
 * NOTE        : Module prefix 'TSG'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef _TSGRAPH_H_
#define _TSGRAPH_H_

#ifdef WIN32
#pragma comment(lib, "tsgraphg")
#pragma comment(exestr, "!!! Copyright (C) 1992-2003. " \
  "Computer Graphics Support Group "                    \
  "of 30 Phys-Math Lyceum.\n"                           \
  "Tough Space Graphics library.")
#endif /* WIN32 */

#include <commondf.h>

/***
 * Useful constants
 ***/

/* Pi number */
#define TSG_PI       3.14159265358979323846

/* E number */
#define TSG_E        2.71828182845904523536

/* Square root of 2 */
#define TSG_SQRT2    1.41421356237309504880

/* Inverse of square root of 3 */
#define TSG_INVSQRT3 0.577350269189627

/***
 * Useful macros
 ***/

/* Convert degree to radians macro */
#define TSG_DTOR(X) ((X) * TSG_PI / 180.0)

/* Convert radians to degrees macro */
#define TSG_RTOD(X) ((X) * 180.0 / TSG_PI)

/***
 * Vectors handle macros
 ***/

/* Set vector coordinates.
 *
 * VOID TSG_SetVec( tsgVEC *V, tsgDBL X, tsgDBL Y, tsgDBL Z );
 */
#define TSG_SetVec(V, A, B, C) \
  ((V)->X = (A), (V)->Y = (B), (V)->Z = (C))

/* Obtain vector coordinates by number (0 - X, 1 - Y, 2 - Z)
 *
 * tsgDBL TSG_GetVecTerm( tsgVEC *V, INT CoordNum );
 */
#define TSG_GetVecTerm(V, CoordNum) \
  (*((tsgDBL *)(V) + (CoordNum)))

/* Add two vectors.
 *
 * VOID TSG_VecAddVec( tsgVEC *VRes, tsgVEC *V1, tsgVEC *V2 );
 */
#define TSG_VecAddVec(VRes, V1, V2) \
  ((VRes)->X = (V1)->X + (V2)->X, \
   (VRes)->Y = (V1)->Y + (V2)->Y, \
   (VRes)->Z = (V1)->Z + (V2)->Z)

/* Add two vectors with assignment.
 *
 * VOID TSG_VecAddVecEq( tsgVEC *VRes, tsgVEC *V1 );
 */
#define TSG_VecAddVecEq(VRes, V1) \
  TSG_VecAddVec(VRes, VRes, V1)

/* Multiply vector by terms.
 *
 * VOID TSG_VecMulVec( tsgVEC *VRes, tsgVEC *V1, tsgVEC *V2 );
 */
#define TSG_VecMulVec(VRes, V1, V2) \
  ((VRes)->X = (V1)->X * (V2)->X, \
   (VRes)->Y = (V1)->Y * (V2)->Y, \
   (VRes)->Z = (V1)->Z * (V2)->Z)

/* Multiply vector by terms with assignment.
 *
 * VOID TSG_VecMulVecEq( tsgVEC *VRes, tsgVEC *V1 );
 */
#define TSG_VecMulVecEq(VRes, V1) \
  TSG_VecMulVecTerm(VRes, VRes, V1)

/* Subtract two vectors.
 *
 * VOID TSG_VecSubVec( tsgVEC *VRes, tsgVEC *V1, tsgVEC *V2 );
 */
#define TSG_VecSubVec(VRes, V1, V2) \
  ((VRes)->X = (V1)->X - (V2)->X, \
   (VRes)->Y = (V1)->Y - (V2)->Y, \
   (VRes)->Z = (V1)->Z - (V2)->Z)

/* Subtract two vectors with assignment.
 *
 * VOID TSG_VecSubVecEq( tsgVEC *VRes, tsgVEC *V1 );
 */
#define TSG_VecSubVecEq(VRes, V1) \
  TSG_VecSubVec(VRes, VRes, V1)

/* Negate vector (V = -V1).
 *
 * VOID TSG_VecNeg( tsgVEC *VRes, tsgVEC *V );
 */
#define TSG_VecNeg(VRes, V) \
  ((VRes)->X = -(V)->X, \
   (VRes)->Y = -(V)->Y, \
   (VRes)->Z = -(V)->Z)

/* Negate vector (V = -V) with assignment.
 *
 * VOID TSG_VecNegEq( tsgVEC *V );
 */
#define TSG_VecNegEq(V) \
  TSG_VecNeg((V), (V))

/* Vector multiplication by number.
 *
 * VOID TSG_VecMulNum( tsgVEC *VRes, tsgVEC *V1, tsgDBL N );
 */
#define TSG_VecMulNum(VRes, V1, N) \
  ((VRes)->X = (V1)->X * (N), \
   (VRes)->Y = (V1)->Y * (N), \
   (VRes)->Z = (V1)->Z * (N))

/* Vector multiplication by number with assignment.
 *
 * VOID TSG_VecMulNumEq( tsgVEC *VRes, tsgDBL N );
 */
#define TSG_VecMulNumEq(VRes, N) \
  TSG_VecMulNum(VRes, VRes, N)

/* Vector division by number.
 *
 * VOID TSG_VecDivNum( tsgVEC *VRes, tsgVEC *V1, tsgDBL N );
 */
#define TSG_VecDivNum(VRes, V1, N) \
  ((VRes)->X = (V1)->X / (N), \
   (VRes)->Y = (V1)->Y / (N), \
   (VRes)->Z = (V1)->Z / (N))

/* Vector division by number with assignment.
 *
 * VOID TSG_VecDivNumEq( tsgVEC *VRes, tsgDBL N );
 */
#define TSG_VecDivNumEq(VRes, N) \
  TSG_VecDivNum(VRes, VRes, N)

/* Vectors dot product.
 *
 * tsgDBL TSG_VecDotVec( tsgVEC *V1, tsgVEC *V2 );
 */
#define TSG_VecDotVec(V1, V2) \
  ((V1)->X * (V2)->X + (V1)->Y * (V2)->Y + (V1)->Z * (V2)->Z)

/* Get vector squared length
 *
 * tsgDBL TSG_VecLenSqr( tsgVEC *V )
 */
#define TSG_VecLenSqr(V) \
  (TSG_VecDotVec((V), (V)))

/* Vectors cross product.
 *
 * VOID TSG_VecCrossVec( tsgVEC *VRes, tsgVEC *V1, tsgVEC *V2 );
 */
#define TSG_VecCrossVec(VRes, V1, V2) \
  ((VRes)->X = (V1)->Y * (V2)->Z - (V1)->Z * (V2)->Y, \
   (VRes)->Y = (V1)->Z * (V2)->X - (V1)->X * (V2)->Z, \
   (VRes)->Z = (V1)->X * (V2)->Y - (V1)->Y * (V2)->X)

/***
 * Planes handle macros
 ***/

/* Set planes components.
 *
 * VOID TSG_SetPlaneND( tsgPLANE *P, tsgVEC *N, tsgDBL D );
 * VOID TSG_SetPlaneABCD( tsgPLANE *P,
 *          tsgDBL A, tsgDBL B, tsgDBL C, tsgDBL D );
 */
#define TSG_SetPlaneND(P, Norm, Dist) \
  ((P)->N.X = (Norm)->X, \
   (P)->N.Y = (Norm)->Y, \
   (P)->N.Z = (Norm)->Z, \
   (P)->D = (Dist))
#define TSG_SetPlaneABCD(P, A, B, C, Dist) \
  ((P)->N.X = (A),  \
   (P)->N.Y = (B),  \
   (P)->N.Z = (C),  \
   (P)->D = (Dist))

/* Substitute points to plane equation
 *
 * tsgDBL TSG_PointToPlane( tsgPLANE *Plane, tsgVEC *P );
 * tsgDBL TSG_PointToPlaneND( tsgVEC *N, tsgDBL D, tsgVEC *P );
 */
#define TSG_PointToPlane(Plane, P) \
    (TSG_VecDotVec(&(Plane)->N, P) - (Plane)->D)
#define TSG_PointToPlaneND(N, D, P) \
    (TSG_VecDotVec(N, P) - (D))

/* Multiply plane equation by number
 *
 * VOID TSG_PlaneMulNum( tsgPLANE *RPlane, tsgPLANE *Plane,
 *          tsgDBL Num );
 */
#define TSG_PlaneMulNum(RPlane, Plane, Num) \
    (TSG_VecMulNum(&(RPlane)->N, &(Plane)->N, Num), \
     ((RPlane)->D = (Plane)->D * (Num)))

/* Multiply plane equation by number with assignment
 *
 * VOID TSG_PlaneMulNumEq( tsgPLANE *Plane, tsgDBL Num );
 */
#define TSG_PlaneMulNumEq(Plane, Num) \
    (TSG_VecMulNum(&(Plane)->N, &(Plane)->N, Num), \
     ((Plane)->D *= (Num)))

/* Division plane equation by number
 *
 * VOID TSG_PlaneDivNum( tsgPLANE *RPlane, tsgPLANE *Plane,
 *          tsgDBL Num );
 */
#define TSG_PlaneDivNum(RPlane, Plane, Num) \
    (TSG_VecDivNum(&(RPlane)->N, &(Plane)->N, Num), \
     ((RPlane)->D = (Plane)->D / (Num)))

/* Division plane equation by number with assignment
 *
 * VOID TSG_PlaneDivNumEq( tsgPLANE *Plane, tsgDBL Num );
 */
#define TSG_PlaneDivNumEq(Plane, Num) \
    (TSG_VecDivNum(&(Plane)->N, &(Plane)->N, Num), \
     ((Plane)->D /= (Num)))

/***
 * Quaternion handle macros
 ***/

/* Set dummy quaternion (unit transformation).
 *
 * VOID TSG_SetQuatUnit( tsgQUAT *Q );
 */
#define TSG_SetQuatUnit(Q) \
  ((Q)->S = (1), (Q)->V.X = 0, (Q)->V.Y = 0, (Q)->V.Z = 0)

/* Set quaternion parameters (without normalizing).
 *
 * VOID TSG_SetQuatSXYZ( tsgQUAT *Q, tsgDBL S, tsgDBL X, tsgDBL Y, tsgDBL Z );
 */
#define TSG_SetQuatSXYZ(Q, W, A, B, C) \
  ((Q)->S = (W), (Q)->V.X = (A), (Q)->V.Y = (B), (Q)->V.Z = (C))

/* Get quaternion squared length.
 *
 * VOID TSG_QuatLen2( tsgQUAT *Q );
 */
#define TSG_QuatLen2(Q) \
  ((Q)->S * (Q)->S + \
   (Q)->V.X * (Q)->V.X + (Q)->V.Y * (Q)->V.Y + (Q)->V.Z * (Q)->V.Z)

/* Add two quaternions.
 *
 * VOID TSG_QuatAddQuat( tsgQUAT *QRes, tsgQUAT *Q1, tsgQUAT *Q1 );
 */
#define TSG_QuatAddQuat(QRes, Q1, Q2) \
  ((QRes)->S = (Q1)->S + (Q2)->S,       \
   (QRes)->V.X = (Q1)->V.X + (Q2)->V.X, \
   (QRes)->V.Y = (Q1)->V.Y + (Q2)->V.Y, \
   (QRes)->V.Z = (Q1)->V.Z + (Q2)->V.Z)

/* Add two quaternions with assigment.
 *
 * VOID TSG_QuatAddQuatEq( tsgQUAT *QRes, tsgQUAT *Q );
 */
#define TSG_QuatAddQuatEq(QRes, Q) \
  TSG_QuatAddQuat(QRes, QRes, Q)

/* Subtrack two quaternions.
 *
 * VOID TSG_QuatSubQuat( tsgQUAT *QRes, tsgQUAT *Q1, tsgQUAT *Q1 );
 */
#define TSG_QuatSubQuat(QRes, Q1, Q2) \
  ((QRes)->S = (Q1)->S - (Q2)->S,       \
   (QRes)->V.X = (Q1)->V.X - (Q2)->V.X, \
   (QRes)->V.Y = (Q1)->V.Y - (Q2)->V.Y, \
   (QRes)->V.Z = (Q1)->V.Z - (Q2)->V.Z)

/* Subtrack two quaternions with assigment.
 *
 * VOID TSG_QuatSubQuatEq( tsgQUAT *QRes, tsgQUAT *Q );
 */
#define TSG_QuatSubQuatEq(QRes, Q) \
  TSG_QuatSubQuat(QRes, QRes, Q)

/* Multiply quaternion by number.
 *
 * VOID TSG_QuatMulNum( tsgQUAT *QRes, tsgQUAT *Q, tsgDBL N );
 */
#define TSG_QuatMulNum(QRes, Q, N) \
  ((QRes)->S = (Q)->S * (N),     \
   (QRes)->V.X = (Q)->V.X * (N), \
   (QRes)->V.Y = (Q)->V.Y * (N), \
   (QRes)->V.Z = (Q)->V.Z * (N))

/* Multiply quaternion by number with assigment.
 *
 * VOID TSG_QuatMulNumEq( tsgQUAT *QRes, tsgDBL N );
 */
#define TSG_QuatMulNumEq(QRes, N) \
  TSG_QuatMulNum(QRes, QRes, N);

/* Divide quaternion by number.
 *
 * VOID TSG_QuatDivNum( tsgQUAT *QRes, tsgQUAT *Q, tsgDBL N );
 */
#define TSG_QuatDivNum(QRes, Q, N) \
  ((QRes)->S = (Q)->S / (N),     \
   (QRes)->V.X = (Q)->V.X / (N), \
   (QRes)->V.Y = (Q)->V.Y / (N), \
   (QRes)->V.Z = (Q)->V.Z / (N))

/* Divide quaternion by number with assigment.
 *
 * VOID TSG_QuatDivNumEq( tsgQUAT *QRes, tsgDBL N );
 */
#define TSG_QuatDivNumEq(QRes, N) \
  TSG_QuatMulNum(QRes, QRes, N);

/***
 * Matrix handle macros
 ***/

/*              3D transformations
 *              ******************
 *
 * The matrices following by this text means:
 *
 *   any compositions of matrix multiplications use as
 *
 * Pnew = Pold * M
 *  where:
 *     M - compositions of transformations (matrix)
 *     Pold - point before transformation (vector)
 *     Pnew - point after transformation (vector)
 *
 * The matrices of transformation are:
 *
 *  Translation:
 *  -----------
 *  T(dx, dy, dz) = Ú  1   0   0   0 ¿
 *                  ³  0   1   0   0 ³
 *                  ³  0   0   1   0 ³
 *                  À dx  dy  dz   1 Ù
 * (dx - shift by X axis, dy - shift by Y axis,
 * dz - shift by Z axis)
 *
 *  Scaling:
 *  -------
 *  S(sx, sy, sz) = Ú sx   0   0   0 ¿
 *                  ³  0  sy   0   0 ³
 *                  ³  0   0  sz   0 ³
 *                  À  0   0   0   1 Ù
 * (sx - scale by X axis, sy - scale by Y axis,
 * sz - scale by Z axis)
 *
 *  Rotation around Z axis:
 *  ---------------------
 *  Rz(Q) =         Ú  cos  sin  0  0 ¿
 *                  ³ -sin  cos  0  0 ³
 *                  ³    0    0  1  0 ³
 *                  À    0    0  0  1 Ù
 * (Q - angle of rotation around Z axis, sin - sin(Q),
 * cos - cos(Q))
 *
 *  Rotation around X axis:
 *  ---------------------
 *  Rx(Q)=          Ú 1    0    0  0 ¿
 *                  ³ 0  cos  sin  0 ³
 *                  ³ 0 -sin  cos  0 ³
 *                  À 0    0    0  1 Ù
 * (Q - angle of rotation around X axis, sin - sin(Q),
 * cos - cos(Q))
 *
 *  Rotation around Y axis:
 *  ---------------------
 *  Ry(Q)=          Ú cos  0 -sin  0 ¿
 *                  ³   0  1    0  0 ³
 *                  ³ sin  0  cos  0 ³
 *                  À   0  0    0  1 Ù
 * (Q - angle of rotation around Y axis, sin - sin(Q),
 * cos - cos(Q))
 */

/* Set matrix to unit one
 *
 * VOID TSG_SetMatrUnit( tsgMATR *M );
 */
#define TSG_SetMatrUnit(M) \
    ((M)->A11 = 1,         \
     (M)->A12 = 0,         \
     (M)->A13 = 0,         \
     (M)->A21 = 0,         \
     (M)->A22 = 1,         \
     (M)->A23 = 0,         \
     (M)->A31 = 0,         \
     (M)->A32 = 0,         \
     (M)->A33 = 1,         \
     (M)->A41 = 0,         \
     (M)->A42 = 0,         \
     (M)->A43 = 0)

/* Set matrix to translation one
 *
 * VOID TSG_SetMatrTranslate( tsgMATR *M,
 *          tsgDBL DX, tsgDBL DY, tsgDBL DZ );
 */
#define TSG_SetMatrTranslate(M, DX, DY, DZ) \
    ((M)->A11 = 1,         \
     (M)->A12 = 0,         \
     (M)->A13 = 0,         \
     (M)->A21 = 0,         \
     (M)->A22 = 1,         \
     (M)->A23 = 0,         \
     (M)->A31 = 0,         \
     (M)->A32 = 0,         \
     (M)->A33 = 1,         \
     (M)->A41 = (DX),      \
     (M)->A42 = (DY),      \
     (M)->A43 = (DZ))

/* Set matrix to scaling one
 *
 * VOID TSG_SetMatrScale( tsgMATR *M,
 *          tsgDBL SX, tsgDBL SY, tsgDBL SZ );
 */
#define TSG_SetMatrScale(M, SX, SY, SZ) \
    ((M)->A11 = (SX), \
     (M)->A12 = 0,    \
     (M)->A13 = 0,    \
     (M)->A21 = 0,    \
     (M)->A22 = (SY), \
     (M)->A23 = 0,    \
     (M)->A31 = 0,    \
     (M)->A32 = 0,    \
     (M)->A33 = (SZ), \
     (M)->A41 = 0,    \
     (M)->A42 = 0,    \
     (M)->A43 = 0)

/* Set matrix to rotation around Z axis one
 *
 * VOID TSG_SetMatrRotateZ( tsgMATR *M, tsgDBL Sin, tsgDBL Cos );
 */
#define TSG_SetMatrRotateZ(M, Sin, Cos) \
    ((M)->A11 = (Cos),     \
     (M)->A12 = (Sin),     \
     (M)->A13 = 0,         \
     (M)->A21 = -(Sin),    \
     (M)->A22 = (Cos),     \
     (M)->A23 = 0,         \
     (M)->A31 = 0,         \
     (M)->A32 = 0,         \
     (M)->A33 = 1,         \
     (M)->A41 = 0,         \
     (M)->A42 = 0,         \
     (M)->A43 = 0)

/* Set matrix to rotation around X axis one
 *
 * VOID TSG_SetMatrRotateX( tsgMATR *M, tsgDBL Sin, tsgDBL Cos );
 */
#define TSG_SetMatrRotateX(M, Sin, Cos) \
    ((M)->A11 = 1,         \
     (M)->A12 = 0,         \
     (M)->A13 = 0,         \
     (M)->A21 = 0,         \
     (M)->A22 = (Cos),     \
     (M)->A23 = (Sin),     \
     (M)->A31 = 0,         \
     (M)->A32 = -(Sin),    \
     (M)->A33 = (Cos),     \
     (M)->A41 = 0,         \
     (M)->A42 = 0,         \
     (M)->A43 = 0)

/* Set matrix to rotation around Y axis one
 *
 * VOID TSG_SetMatrRotateY( tsgMATR *M, tsgDBL Sin, tsgDBL Cos );
 */
#define TSG_SetMatrRotateY(M, Sin, Cos) \
    ((M)->A11 = (Cos),     \
     (M)->A12 = 0,         \
     (M)->A13 = -(Sin),    \
     (M)->A21 = 0,         \
     (M)->A22 = 1,         \
     (M)->A23 = 0,         \
     (M)->A31 = (Sin),     \
     (M)->A32 = 0,         \
     (M)->A33 = (Cos),     \
     (M)->A41 = 0,         \
     (M)->A42 = 0,         \
     (M)->A43 = 0)

/* Multiply matrix by a number
 *
 * VOID TSG_MatrMulNum( tsgMATR *MRes, tsgMATR *M, tsgDBL Num );
 */
#define TSG_MatrMulNum(MRes, M, Num) \
  ((MRes)->A11 = (M)->A11 * (Num), \
   (MRes)->A12 = (M)->A12 * (Num), \
   (MRes)->A13 = (M)->A13 * (Num), \
   (MRes)->A21 = (M)->A21 * (Num), \
   (MRes)->A22 = (M)->A22 * (Num), \
   (MRes)->A23 = (M)->A23 * (Num), \
   (MRes)->A31 = (M)->A31 * (Num), \
   (MRes)->A32 = (M)->A32 * (Num), \
   (MRes)->A33 = (M)->A33 * (Num), \
   (MRes)->A41 = (M)->A41 * (Num), \
   (MRes)->A42 = (M)->A42 * (Num), \
   (MRes)->A43 = (M)->A43 * (Num))

/* Divide matrix by a number
 *
 * VOID TSG_MatrDivNum( tsgMATR *MRes, tsgMATR *M, tsgDBL Num );
 */
#define TSG_MatrDivNum(MRes, M, Num) \
  ((MRes)->A11 = (M)->A11 / (Num), \
   (MRes)->A12 = (M)->A12 / (Num), \
   (MRes)->A13 = (M)->A13 / (Num), \
   (MRes)->A21 = (M)->A21 / (Num), \
   (MRes)->A22 = (M)->A22 / (Num), \
   (MRes)->A23 = (M)->A23 / (Num), \
   (MRes)->A31 = (M)->A31 / (Num), \
   (MRes)->A32 = (M)->A32 / (Num), \
   (MRes)->A33 = (M)->A33 / (Num), \
   (MRes)->A41 = (M)->A41 / (Num), \
   (MRes)->A42 = (M)->A42 / (Num), \
   (MRes)->A43 = (M)->A43 / (Num))

/* Multiply matrix by a number with assignment
 *
 * VOID TSG_MatrMulNumEq( tsgMATR *MRes, tsgDBL Num );
 */
#define TSG_MatrMulNumEq(MRes, Num) \
  ((MRes)->A11 *= (Num), \
   (MRes)->A12 *= (Num), \
   (MRes)->A13 *= (Num), \
   (MRes)->A21 *= (Num), \
   (MRes)->A22 *= (Num), \
   (MRes)->A23 *= (Num), \
   (MRes)->A31 *= (Num), \
   (MRes)->A32 *= (Num), \
   (MRes)->A33 *= (Num), \
   (MRes)->A41 *= (Num), \
   (MRes)->A42 *= (Num), \
   (MRes)->A43 *= (Num))

/* Divide matrix by a number with assignment
 *
 * VOID TSG_MatrDivNumEq( tsgMATR *MRes, tsgDBL Num );
 */
#define TSG_MatrDivNumEq(MRes, Num) \
  ((MRes)->A11 /= (Num), \
   (MRes)->A12 /= (Num), \
   (MRes)->A13 /= (Num), \
   (MRes)->A21 /= (Num), \
   (MRes)->A22 /= (Num), \
   (MRes)->A23 /= (Num), \
   (MRes)->A31 /= (Num), \
   (MRes)->A32 /= (Num), \
   (MRes)->A33 /= (Num), \
   (MRes)->A41 /= (Num), \
   (MRes)->A42 /= (Num), \
   (MRes)->A43 /= (Num))

/***
 * Transformation structure handle macros
 ***/

/* Set transformation structure to unit one
 *
 * VOID TSG_SetTransUnit( tsgTRANS *T );
 */
#define TSG_SetTransUnit(T) \
    (TSG_SetMatrUnit(&(T)->M),    \
     TSG_SetMatrUnit(&(T)->InvM))

/* Set transformation structure to translation one
 *
 * VOID TSG_SetTransTranslate( tsgTRANS *T,
 *          tsgDBL DX, tsgDBL DY, tsgDBL DZ );
 */
#define TSG_SetTransTranslate(T, DX, DY, DZ) \
    (TSG_SetMatrTranslate(&(T)->M, DX, DY, DZ),             \
     TSG_SetMatrTranslate(&(T)->InvM, -(DX), -(DY), -(DZ)))

/* Set transformation structure to scaling one
 *
 * VOID TSG_SetTransScale( tsgTRANS *T,
 *          tsgDBL SX, tsgDBL SY, tsgDBL SZ );
 */
#define TSG_SetTransScale(T, SX, SY, SZ) \
    (TSG_SetMatrScale(&(T)->M, SX, SY, SZ), \
     TSG_SetMatrScale(&(T)->InvM,           \
       1.0 / (SX), 1.0 / (SY), 1.0 / (SZ)))

/* Set transformation structure to rotation around Z axis one
 *
 * VOID TSG_SetTransRotateZ( tsgTRANS *T, tsgDBL Sin, tsgDBL Cos );
 */
#define TSG_SetTransRotateZ(T, Sin, Cos) \
    (TSG_SetMatrRotateZ(&(T)->M, Sin, Cos),    \
     TSG_SetMatrRotateZ(&(T)->InvM, -(Sin), Cos))

/* Set transformation structure to rotation around X axis one
 *
 * VOID TSG_SetTransRotateX( tsgTRANS *T, tsgDBL Sin, tsgDBL Cos );
 */
#define TSG_SetTransRotateX(T, Sin, Cos) \
    (TSG_SetMatrRotateX(&(T)->M, Sin, Cos),    \
     TSG_SetMatrRotateX(&(T)->InvM, -(Sin), Cos))

/* Set transformation structure to rotation around Y axis one
 *
 * VOID TSG_SetTransRotateY( tsgTRANS *T, tsgDBL Sin, tsgDBL Cos );
 */
#define TSG_SetTransRotateY(T, Sin, Cos) \
    (TSG_SetMatrRotateY(&(T)->M, Sin, Cos),    \
     TSG_SetMatrRotateY(&(T)->InvM, -(Sin), Cos))

/***
 * Ray handle macros
 ***/

/* Set ray by two vectors (origin and direction)
 *
 * VOID TSG_SetRay( tsgRAY *Ray, tsgVEC *Origin,
 *          tsgVEC *Direction );
 */
#define TSG_SetRay(Ray, Origin, Direction) \
  ((Ray)->Org = *(Origin),   \
   (Ray)->Dir = *(Direction))

/* Substitute number to ray (obtain ray point)
 *
 * VOID TSG_PointToRay( tsgVEC *VRes, tsgRAY *Ray, tsgDBL T );
 */
#define TSG_PointToRay(VRes, Ray, T) \
  ((VRes)->X = (Ray)->Org.X + (Ray)->Dir.X * (T), \
   (VRes)->Y = (Ray)->Org.Y + (Ray)->Dir.Y * (T), \
   (VRes)->Z = (Ray)->Org.Z + (Ray)->Dir.Z * (T))

/***
 * Base space (3D) graphics types definitions
 ***/

/* Base float point type for all purpose */
typedef FLOAT tsgDBL;

/* Space vectors, points, colors and so on storage structure */
typedef struct tagtsgVEC
{
  tsgDBL X, Y, Z; /* Space coordinates */
} tsgVEC;

/* Space (3D) plane equation structure */
typedef struct tagtsgPLANE
{
  /* Point 'P' lies at plane (N, D) if:
   *      N * P - D = 0
   * or if N = (A, B, C) and P = (x, y, z):
   *      A * x + B * y + C * z - D = 0
   */
  tsgVEC N; /* Normal vector (should be normalized) */
  tsgDBL D; /* Offset value */
} tsgPLANE;

/* Ray: direction from fixed point */
typedef struct tagtsgRAY
{
  tsgVEC
    Org, /* Origin ray point */
    Dir; /* Ray direction (should be normalized) */
} tsgRAY;

/* Quaternion: hypercomplex number (s + i*x + j*y + k*z).
 * Should be normalized: (s * s + x * x + y * y + z * z = 1).
 * Value means: [cos(a/2), sin(a/2)*(x,y,z)],
 * where: a - angle of rotation, (x,y,z) - rotation axis. */
typedef struct tagtsgQUAT
{
  tsgVEC V; /* Imaginary part of quaternion (x, y, z) */
  tsgDBL S; /* Real part of quaternion */
} tsgQUAT;

/* Transformation matrix storage type */
typedef struct tagtsgMATR
{
  tsgDBL
    A11, A12, A13,
    A21, A22, A23,
    A31, A32, A33,
    A41, A42, A43;
} tsgMATR;

/* Transformation storage type */
typedef struct tagtsgTRANS
{
  tsgMATR
    M,    /* Direct transformation matrix */
    InvM; /* Inverse transformation matrix */
} tsgTRANS;

/* Camera storage type */
typedef struct tagtsgCAMERA
{
  /* Camera space data */
  tsgVEC Loc;           /* Camera location */
  tsgVEC Up;            /* Camera up direction */
  tsgVEC Right;         /* Camera right direction */
  tsgVEC Dir;           /* Camera direction */
  tsgDBL ProjDistance;  /* Distance to projection plane */
  tsgDBL FarClip;       /* Distance to far clip plane */
  tsgVEC LookAt;        /* Stored for user purpose */

  tsgTRANS T;           /* Camera tranformation structure */

  /* Project plane size */
  tsgDBL ProjPlaneWidth, ProjPlaneHeight;

  /* Screen (drawing image) size (halfs) */
  INT ScreenWidth, ScreenHeight;

  /* Scale factors of screen to project plane size */
  tsgDBL XFactor, YFactor;
} tsgCAMERA;

/*****************************************
 * Base space (3D) mathematics functions *
 *****************************************/

/***
 * Vector (point) transformation handle
 ***/

/* Rotate vector by X axis function */
VOID TSG_VecRotateX( tsgVEC *VRes, tsgVEC *V,
         tsgDBL SinQ, tsgDBL CosQ );
/* Rotate vector by Y axis function */
VOID TSG_VecRotateY( tsgVEC *VRes, tsgVEC *V,
         tsgDBL SinQ, tsgDBL CosQ );
/* Rotate vector by Z axis function */
VOID TSG_VecRotateZ( tsgVEC *VRes, tsgVEC *V,
         tsgDBL SinQ, tsgDBL CosQ );
/* Scale vector function */
VOID TSG_VecScale( tsgVEC *VRes, tsgVEC *V,
         tsgDBL SX, tsgDBL SY, tsgDBL SZ );
/* Translate vector function */
VOID TSG_VecTranslate( tsgVEC *VRes, tsgVEC *V,
         tsgDBL DX, tsgDBL DY, tsgDBL DZ );
/* Multiply vector by matrix */
VOID TSG_VecMulMatr( tsgVEC *VRes, tsgVEC *V, tsgMATR *M );
/* Transform vector */
VOID TSG_VecTransform( tsgVEC *VRes, tsgVEC *V, tsgTRANS *T );
/* Inverse transform vector */
VOID TSG_VecInvTransform( tsgVEC *VRes, tsgVEC *V, tsgTRANS *T );

/* Transform direction (use only left upper 3x3 submatrix) */
VOID TSG_DirTransform( tsgVEC *VRes, tsgVEC *V, tsgTRANS *T );
/* Inverse transform direction (use only left upper 3x3 submatrix) */
VOID TSG_DirInvTransform( tsgVEC *VRes, tsgVEC *V, tsgTRANS *T );

/* Transform normal direction (use only transpose left upper 3x3
 * inverse submatrix) */
VOID TSG_NormTransform( tsgVEC *VRes, tsgVEC *V, tsgTRANS *T );
/* Inverse transform normal direction (use only transpose left
 * upper 3x3 direct submatrix) */
VOID TSG_NormInvTransform( tsgVEC *VRes, tsgVEC *V, tsgTRANS *T );

/* Normalize vector function (return old vector length) */
tsgDBL TSG_VecNormalize( tsgVEC *VRes, tsgVEC *V );

/* Rotate vector by X axis function with assignment
 *
 * VOID TSG_VecRotateXEq( tsgVEC *V, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_VecRotateXEq(V, SinQ, CosQ) \
    (TSG_VecRotateX((V), (V), (SinQ), (CosQ)))
/* Rotate vector by Y axis with assignment
 *
 * VOID TSG_VecRotateYEq( tsgVEC *V, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_VecRotateYEq(V, SinQ, CosQ) \
    (TSG_VecRotateY((V), (V), (SinQ), (CosQ)))
/* Rotate vector by Z axis with assignment
 *
 * VOID TSG_VecRotateZEq( tsgVEC *V, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_VecRotateZEq(V, SinQ, CosQ) \
    (TSG_VecRotateZ((V), (V), (SinQ), (CosQ)))
/* Scale vector with assignment
 *
 * VOID TSG_VecScaleEq( tsgVEC *V,
 *           tsgDBL SX, tsgDBL SY, tsgDBL SZ );
 */
#define TSG_VecScaleEq(V, SX, SY, SZ) \
    (TSG_VecScale((V), (V), (SX), (SY), (SZ)))
/* Translate vector with assignment
 *
 * VOID TSG_VecTranslateEq( tsgVEC *V,
 *           tsgDBL DX, tsgDBL DY, tsgDBL DZ );
 */
#define TSG_VecTranslateEq(V, SX, SY, SZ) \
    (TSG_VecTranslate((V), (V), (SX), (SY), (SZ)))
/* Multiply vector by matrix with assignment
 *
 * VOID TSG_VecMulMatrEq( tsgVEC *V, tsgMATR *M );
 */
#define TSG_VecMulMatrEq(V, M) \
    (TSG_VecMulMatr((V), (V), (M)))
/* Transform vector with assignment
 *
 * VOID TSG_VecTransformEq( tsgVEC *V, tsgTRANS *T );
 */
#define TSG_VecTransformEq(V, T) \
    (TSG_VecTransform((V), (V), (T)))
/* Inverse transform vector with assignment
 *
 * VOID TSG_VecInvTransformEq( tsgVEC *V, tsgTRANS *T );
 */
#define TSG_VecInvTransformEq(V, T) \
    (TSG_VecInvTransform((V), (V), (T)))

/* Transform direction (use only left upper 3x3 submatrix)
 * with assignment
 *
 * VOID TSG_DirTransformEq( tsgVEC *V, tsgTRANS *T );
 */
#define TSG_DirTransformEq(V, T) \
    (TSG_DirTransform((V), (V), (T)))
/* Inverse transform direction (use only left upper 3x3
 * submatrix) with assignment
 *
 * VOID TSG_DirInvTransformEq( tsgVEC *V, tsgTRANS *T );
 */
#define TSG_DirInvTransformEq(V, T) \
    (TSG_DirInvTransform((V), (V), (T)))

/* Transform direction (use only left upper 3x3 submatrix)
 * with assignment
 *
 * VOID TSG_DirTransformEq( tsgVEC *V, tsgTRANS *T );
 */
#define TSG_DirTransformEq(V, T) \
    (TSG_DirTransform((V), (V), (T)))
/* Inverse transform direction (use only left upper 3x3
 * submatrix) with assignment
 *
 * VOID TSG_DirInvTransformEq( tsgVEC *V, tsgTRANS *T );
 */
#define TSG_DirInvTransformEq(V, T) \
    (TSG_DirInvTransform((V), (V), (T)))

/* Transform normal direction (use only transpose left upper
 * 3x3 inverse submatrix) with assignment
 *
 * VOID TSG_NormTransformEq( tsgVEC *V, tsgTRANS *T );
 */
#define TSG_NormTransformEq(V, T) \
    (TSG_NormTransform((V), (V), (T)))
/* Inverse transform normal direction (use only transpose left
 * upper 3x3 direct submatrix) with assignment
 *
 * VOID TSG_NormInvTransformEq( tsgVEC *V, tsgTRANS *T );
 */
#define TSG_NormInvTransformEq(V, T) \
    (TSG_NormInvTransform((V), (V), (T)))

/* Normalize vector function (return old vector length)
 * with assignment
 *
 * tsgDBL TSG_VecNormalizeEq( tsgVEC *V );
 */
#define TSG_VecNormalizeEq(V) \
    (TSG_VecNormalize((V), (V)))

/***
 * Ray transformation handle
 ***/

/* Rotate ray by X axis */
VOID TSG_RayRotateX( tsgRAY *RRes, tsgRAY *R,
         tsgDBL SinQ, tsgDBL CosQ );
/* Rotate ray by Y axis */
VOID TSG_RayRotateY( tsgRAY *RRes, tsgRAY *R,
         tsgDBL SinQ, tsgDBL CosQ );
/* Rotate ray around Z axis */
VOID TSG_RayRotateZ( tsgRAY *RRes, tsgRAY *R,
         tsgDBL SinQ, tsgDBL CosQ );
/* Scale ray (return direction length before normalize) */
tsgDBL TSG_RayScale( tsgRAY *RRes, tsgRAY *R,
           tsgDBL SX, tsgDBL SY, tsgDBL SZ );
/* Translate ray */
VOID TSG_RayTranslate( tsgRAY *RRes, tsgRAY *R,
         tsgDBL DX, tsgDBL DY, tsgDBL DZ );
/* Multiply ray by matrix (return direction length before
 * normalize) */
tsgDBL TSG_RayMulMatr( tsgRAY *RRes, tsgRAY *R, tsgMATR *M );
/* Transform ray (return direction length before
 * normalizing) */
tsgDBL TSG_RayTransform( tsgRAY *RRes, tsgRAY *R, tsgTRANS *T );
/* Inverse transform ray (return direction length before
 * normalizing) */
tsgDBL TSG_RayInvTransform( tsgRAY *RRes, tsgRAY *R, tsgTRANS *T );

/* Set ray by two points (return initial direction length) */
tsgDBL TSG_SetRayBy2Points( tsgRAY *RRes, tsgVEC *P1, tsgVEC *P2 );

/* Rotate ray by X axis function with assignment
 *
 * VOID TSG_RayRotateXEq( tsgRAY *R, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_RayRotateXEq(R, SinQ, CosQ) \
    (TSG_RayRotateX((R), (R), (SinQ), (CosQ)))
/* Rotate ray by Y axis with assignment
 *
 * VOID TSG_RayRotateYEq( tsgRAY *R, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_RayRotateYEq(R, SinQ, CosQ) \
    (TSG_RayRotateY((R), (R), (SinQ), (CosQ)))
/* Rotate ray by Z axis with assignment
 *
 * VOID TSG_RayRotateZEq( tsgRAY *R, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_RayRotateZEq(R, SinQ, CosQ) \
    (TSG_RayRotateZ((R), (R), (SinQ), (CosQ)))
/* Scale ray with assignment (return direction length before
 * normalize)
 *
 * tsgDBL TSG_RayScaleEq( tsgRAY *R,
 *            tsgDBL SX, tsgDBL SY, tsgDBL SZ );
 */
#define TSG_RayScaleEq(R, SX, SY, SZ) \
    (TSG_RayScale((R), (R), (SX), (SY), (SZ)))
/* Translate ray with assignment
 *
 * VOID TSG_RayTranslateEq( tsgRAY *R,
 *          tsgDBL DX, tsgDBL DY, tsgDBL DZ );
 */
#define TSG_RayTranslateEq(R, SX, SY, SZ) \
    (TSG_RayTranslate((R), (R), (SX), (SY), (SZ)))
/* Multiply ray by matrix with assignment (return direction
 * length before normalize)
 *
 * tsgDBL TSG_RayMulMatrEq( tsgRAY *R, tsgMATR *M );
 */
#define TSG_RayMulMatrEq(R, M) \
    (TSG_RayMulMatr((R), (R), (M)))
/* Transform ray with assignment (return direction length
 * before normalize)
 *
 * tsgDBL TSG_RayTransformEq( tsgRAY *R, tsgTRANS *T );
 */
#define TSG_RayTransformEq(R, T) \
    (TSG_RayTransform((R), (R), (T)))
/* Inverse transform ray with assignment (return direction
 * length before normalize)
 *
 * tsgDBL TSG_RayInvTransformEq( tsgRAY *R, tsgTRANS *T );
 */
#define TSG_RayInvTransformEq(R, T) \
    (TSG_RayInvTransform((R), (R), (T)))

/***
 * Plane transformation handle
 ***/

/* Rotate plane by X axis */
VOID TSG_PlaneRotateX( tsgPLANE *PRes, tsgPLANE *Plane,
         tsgDBL SinQ, tsgDBL CosQ );
/* Rotate plane by Y axis */
VOID TSG_PlaneRotateY( tsgPLANE *PRes, tsgPLANE *Plane,
         tsgDBL SinQ, tsgDBL CosQ );
/* Rotate plane by Z axis */
VOID TSG_PlaneRotateZ( tsgPLANE *PRes, tsgPLANE *Plane,
         tsgDBL SinQ, tsgDBL CosQ );
/* Scale plane */
VOID TSG_PlaneScale( tsgPLANE *PRes, tsgPLANE *Plane,
         tsgDBL SX, tsgDBL SY, tsgDBL SZ );
/* Translate plane */
VOID TSG_PlaneTranslate( tsgPLANE *PRes, tsgPLANE *Plane,
         tsgDBL DX, tsgDBL DY, tsgDBL DZ );
/* Transform plane */
VOID TSG_PlaneTransform( tsgPLANE *PRes, tsgPLANE *Plane,
         tsgTRANS *T );
/* Inverse transform plane */
VOID TSG_PlaneInvTransform( tsgPLANE *PRes, tsgPLANE *Plane,
         tsgTRANS *T );

/* Rotate plane by X axis function with assignment
 *
 * VOID TSG_PlaneRotateXEq( tsgPLANE *P, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_PlaneRotateXEq(P, SinQ, CosQ) \
    (TSG_PlaneRotateX((P), (P), (SinQ), (CosQ)))
/* Rotate plane by Y axis with assignment
 *
 * VOID TSG_PlaneRotateYEq( tsgPLANE *P, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_PlaneRotateYEq(P, SinQ, CosQ) \
    (TSG_PlaneRotateY((P), (P), (SinQ), (CosQ)))
/* Rotate plane by Z axis with assignment
 *
 * VOID TSG_PlaneRotateZEq( tsgPLANE *P, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_PlaneRotateZEq(P, SinQ, CosQ) \
    (TSG_PlaneRotateZ((P), (P), (SinQ), (CosQ)))
/* Scale plane with assignment
 *
 * VOID TSG_PlaneScaleEq( tsgPLANE *P,
 *           tsgDBL SX, tsgDBL SY, tsgDBL SZ );
 */
#define TSG_PlaneScaleEq(P, SX, SY, SZ) \
    (TSG_PlaneScale((P), (P), (SX), (SY), (SZ)))
/* Translate plane with assignment
 *
 * VOID TSG_PlaneTranslateEq( tsgPLANE *P,
 *           tsgDBL DX, tsgDBL DY, tsgDBL DZ );
 */
#define TSG_PlaneTranslateEq(P, SX, SY, SZ) \
    (TSG_PlaneTranslate((P), (P), (SX), (SY), (SZ)))
/* Transform plane with assignment
 *
 * VOID TSG_PlaneTransformEq( tsgPLANE *P, tsgTRANS *T );
 */
#define TSG_PlaneTransformEq(P, T) \
    (TSG_PlaneTransform((P), (P), (T)))
/* Inverse transform plane with assignment
 *
 * VOID TSG_PlaneInvTransformEq( tsgPLANE *P, tsgTRANS *T );
 */
#define TSG_PlaneInvTransformEq(P, T) \
    (TSG_PlaneInvTransform((P), (P), (T)))

/* Determine plane equation by three belonging points,
 * normal determine by pairs: (P1, P2) and (P1, P3); so
 * all points get in anti clockwise order from front plane
 * side (from normal direction).
 * (return FALSE if plane has zero normal)
 */
BOOL TSG_PlaneBy3Points( tsgPLANE *Plane,
         tsgVEC *P1, tsgVEC *P2, tsgVEC *P3 );
BOOL TSG_PlaneBy3PointsND( tsgVEC *N, tsgDBL *D,
         tsgVEC *P1, tsgVEC *P2, tsgVEC *P3 );

/***
 * Quaternion handle
 ***/

/* Set quaternion parameters by angle (in radians) and rotation vector */
VOID TSG_QuatByAXYZ( tsgQUAT *Q, tsgDBL Angle, tsgDBL X, tsgDBL Y, tsgDBL Z );

/* Set quaternion parameters by angle sine, cosine and rotation vector */
VOID TSG_QuatBySinCosXYZ( tsgQUAT *Q, tsgDBL Sin,
         tsgDBL Cos, tsgDBL X, tsgDBL Y, tsgDBL Z );

/* Quaternion normalizing */
VOID TSG_QuatNormalize( tsgQUAT *QRes, tsgQUAT *Q);

/* Spherical interpolation of two quaternions */
VOID TSG_QuatSLerp( tsgQUAT *QRes, tsgQUAT *Q1, tsgQUAT *Q2, tsgDBL T );

/* Multiplication of two quaternions */
VOID TSG_QuatMulQuat( tsgQUAT *QRes, tsgQUAT *Q1, tsgQUAT *Q2 );

/* Convert quaternion to rotation matrix */
VOID TSG_MatrByQuat( tsgMATR *MRes, tsgQUAT *Q );

/* Convert quaternion to transformation */
VOID TSG_TransByQuat( tsgTRANS *TRes, tsgQUAT *Q );

/* Transform vector by quaternion */
VOID TSG_VecRotateByQuat( tsgVEC *VRes, tsgVEC *V, tsgQUAT *Q );

/* Transform vector by arbitrary axis */
VOID TSG_VecRotate( tsgVEC *VRes, tsgVEC *V, tsgDBL Sin, tsgDBL Cos,
         tsgDBL X, tsgDBL Y, tsgDBL Z );

/* Quaternion normalizing function with assignment
 *
 * VOID TSG_QuatNormalizeEq( tsgQUAT *Q );
 */
#define TSG_QuatNormalizeEq(Q) \
    (TSG_QuatNormalize(Q, Q))

/* Multiplication of two quaternions with assigment
 *
 * VOID TSG_QuatMulQuatEq( tsgQUAT *QRes, tsgQUAT *Q );
 */
#define TSG_QuatMulQuatEq(QRes, Q) \
  TSG_QuatMulQuat(QRes, QRes, Q)

/***
 * Matrix transformation handle
 ***/

/* Rotate matrix around X axis */
VOID TSG_MatrRotateX( tsgMATR *MRes, tsgMATR *Matr,
         tsgDBL SinQ, tsgDBL CosQ );
/* Rotate matrix around Y axis */
VOID TSG_MatrRotateY( tsgMATR *MRes, tsgMATR *Matr,
         tsgDBL SinQ, tsgDBL CosQ );
/* Rotate matrix around Z axis function */
VOID TSG_MatrRotateZ( tsgMATR *MRes, tsgMATR *Matr,
         tsgDBL SinQ, tsgDBL CosQ );
/* Scale matrix */
VOID TSG_MatrScale( tsgMATR *MRes, tsgMATR *Matr,
         tsgDBL SX, tsgDBL SY, tsgDBL SZ );
/* Translation of matrix function */
VOID TSG_MatrTranslate( tsgMATR *MRes, tsgMATR *Matr,
         tsgDBL DX, tsgDBL DY, tsgDBL DZ );
/* Multiply matrix by matrix */
VOID TSG_MatrMulMatr( tsgMATR *MRes, tsgMATR *M1, tsgMATR *M2 );
/* Transformation matrix by matrix */
VOID TSG_MatrTransform( tsgMATR *MRes, tsgMATR *M, tsgTRANS *T );
/* Inverse transformation matrix by matrix */
VOID TSG_MatrInvTransform( tsgMATR *MRes, tsgMATR *M, tsgTRANS *T );

/* Rotate matrix by X axis function with assignment
 *
 * VOID TSG_MatrRotateXEq( tsgMATR *M, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_MatrRotateXEq(M, SinQ, CosQ) \
    (TSG_MatrRotateX((M), (M), (SinQ), (CosQ)))
/* Rotate matrix by Y axis with assignment
 *
 * VOID TSG_MatrRotateYEq( tsgMATR *M, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_MatrRotateYEq(M, SinQ, CosQ) \
    (TSG_MatrRotateY((M), (M), (SinQ), (CosQ)))
/* Rotate matrix by Z axis with assignment
 *
 * VOID TSG_MatrRotateZEq( tsgMATR *M, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_MatrRotateZEq(M, SinQ, CosQ) \
    (TSG_MatrRotateZ((M), (M), (SinQ), (CosQ)))
/* Scale matrix with assignment
 *
 * VOID TSG_MatrScaleEq( tsgMATR *M,
 *           tsgDBL SX, tsgDBL SY, tsgDBL SZ );
 */
#define TSG_MatrScaleEq(M, SX, SY, SZ) \
    (TSG_MatrScale((M), (M), (SX), (SY), (SZ)))
/* Translate matrix with assignment
 *
 * VOID TSG_MatrTranslateEq( tsgMATR *M,
 *           tsgDBL DX, tsgDBL DY, tsgDBL DZ );
 */
#define TSG_MatrTranslateEq(M, SX, SY, SZ) \
    (TSG_MatrTranslate((M), (M), (SX), (SY), (SZ)))
/* Multiply matrix by matrix with assignment
 *
 * VOID TSG_MatrMulMatrEq( tsgMATR *M, tsgMATR *M );
 */
#define TSG_MatrMulMatrEq(MRes, M) \
    (TSG_MatrMulMatr((MRes), (MRes), (M)))
/* Transform matrix with assignment
 *
 * VOID TSG_MatrTransformEq( tsgMATR *M, tsgTRANS *T );
 */
#define TSG_MatrTransformEq(M, T) \
    (TSG_MatrTransform((M), (M), (T)))
/* Inverse transform matrix with assignment
 *
 * VOID TSG_MatrInvTransformEq( tsgMATR *M, tsgTRANS *T );
 */
#define TSG_MatrInvTransformEq(M, T) \
    (TSG_MatrInvTransform((M), (M), (T)))
/* Obtain inverse transformation matrix */
BOOL TSG_MatrInv( tsgMATR *MRes, tsgMATR *M );

/***
 * Transformation structure transformation handle
 ***/

/* Rotate transformation structure around Z axis function */
VOID TSG_TransRotateX( tsgTRANS *TRes, tsgTRANS *Trans,
         tsgDBL SinQ, tsgDBL CosQ );
/* Rotate transformation structure around Y axis function */
VOID TSG_TransRotateY( tsgTRANS *TRes, tsgTRANS *Trans,
         tsgDBL SinQ, tsgDBL CosQ );
/* Rotate transformation structure around Z axis function */
VOID TSG_TransRotateZ( tsgTRANS *TRes, tsgTRANS *Trans,
         tsgDBL SinQ, tsgDBL CosQ );
/* Scale transformation structure function */
VOID TSG_TransScale( tsgTRANS *TRes, tsgTRANS *Trans,
         tsgDBL SX, tsgDBL SY, tsgDBL SZ );
/* Translate transformation structure function */
VOID TSG_TransTranslate( tsgTRANS *TRes, tsgTRANS *Trans,
         tsgDBL DX, tsgDBL DY, tsgDBL DZ );
/* Transform transformation structure function */
VOID TSG_TransTransform( tsgTRANS *TRes, tsgTRANS *Trans,
         tsgTRANS *T );
/* Inverse transform transformation structure function */
VOID TSG_TransInvTransform( tsgTRANS *TRes, tsgTRANS *Trans,
         tsgTRANS *T );

/* Rotate transformation structure by X axis function
 * with assignment
 *
 * VOID TSG_TransRotateXEq( tsgTRANS *T, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_TransRotateXEq(T, SinQ, CosQ) \
    (TSG_TransRotateX((T), (T), (SinQ), (CosQ)))
/* Rotate transformation structure by Y axis with assignment
 *
 * VOID TSG_TransRotateYEq( tsgTRANS *T, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_TransRotateYEq(T, SinQ, CosQ) \
    (TSG_TransRotateY((T), (T), (SinQ), (CosQ)))
/* Rotate transformation structure by Z axis with assignment
 *
 * VOID TSG_TransRotateZEq( tsgTRANS *T, tsgDBL SinQ, tsgDBL CosQ );
 */
#define TSG_TransRotateZEq(T, SinQ, CosQ) \
    (TSG_TransRotateZ((T), (T), (SinQ), (CosQ)))
/* Scale transformation structure with assignment
 *
 * VOID TSG_TransScaleEq( tsgTRANS *T,
 *           tsgDBL SX, tsgDBL SY, tsgDBL SZ );
 */
#define TSG_TransScaleEq(T, SX, SY, SZ) \
    (TSG_TransScale((T), (T), (SX), (SY), (SZ)))
/* Translate transformation structure with assignment
 *
 * VOID TSG_TransTranslateEq( tsgTRANS *T,
 *           tsgDBL DX, tsgDBL DY, tsgDBL DZ );
 */
#define TSG_TransTranslateEq(T, SX, SY, SZ) \
    (TSG_TransTranslate((T), (T), (SX), (SY), (SZ)))
/* Transform transformation structure with assignment
 *
 * VOID TSG_TransTransformEq( tsgTRANS *T, tsgTRANS *T );
 */
#define TSG_TransTransformEq(TRes, T) \
    (TSG_TransTransform((TRes), (TRes), (T)))
/* Inverse transform transformation structure with assignment
 *
 * VOID TSG_TransInvTransformEq( tsgTRANS *T, tsgTRANS *T );
 */
#define TSG_TransInvTransformEq(TRes, T) \
    (TSG_TransInvTransform((TRes), (TRes), (T)))

/* Set transformation by matrix function */
VOID TSG_SetTransByMatr( tsgTRANS *TRes, tsgMATR *M );

/***
 * Camera structure transformation and manipulation handle
 ***/

/*** Camera setup ***/

/* Set camera view common parameters */
VOID TSG_CameraSetup( tsgCAMERA *Cam,
         tsgDBL ProjDistance, tsgDBL FarClip,
         tsgDBL ProjPlaneWidth, tsgDBL ProjPlaneHeight,
         INT ScreenWidth, INT ScreenHeight );

/* Setup camera data by location, direction and up vector */
VOID TSG_CameraUpdateLocDirUp( tsgCAMERA *Cam );

/* Setup camera data by location, 'lookat point' and up vector */
VOID TSG_CameraUpdateLocLookAtUp( tsgCAMERA *Cam );

/*** Camera applying ***/

/* Calculate project of point to camera view */
VOID TSG_CameraApplyWorldToCamera( tsgCAMERA *Cam, tsgVEC *PCamera,
         tsgVEC *PWorld );

/* Calculate project of world point to screen */
VOID TSG_CameraApplyWorldToScreen( tsgCAMERA *Cam, INT XY[2],
         tsgVEC *PWorld);

/* Calculate project of camera project plane point to screen */
VOID TSG_CameraApplyCameraToScreen( tsgCAMERA *Cam, INT XY[2],
         tsgVEC *PCamera );

/* Calculate ray from location to specified screen point, ray
 * started from project plane */
VOID TSG_CameraApplyScreenToRay( tsgCAMERA *Cam, tsgRAY *Ray,
         tsgDBL X, tsgDBL Y );

/*** Camera transformation ***/

/*** Movement and rotation along camera directions ***/
/* Move camera forward/backward along 'Dir' direction */
VOID TSG_CameraMoveByDir( tsgCAMERA *Cam, tsgDBL Distance );
/* Move camera up/down along 'Up' direction */
VOID TSG_CameraMoveByUp( tsgCAMERA *Cam, tsgDBL Distance );
/* Move camera left/right along 'Right' direction */
VOID TSG_CameraMoveByRight( tsgCAMERA *Cam, tsgDBL Distance );
/* Rotate camera along 'Dir' direction */
VOID TSG_CameraRotateByDir( tsgCAMERA *Cam,
         tsgDBL SinRU, tsgDBL CosRU );
/* Rotate camera along 'Up' direction */
VOID TSG_CameraRotateByUp( tsgCAMERA *Cam,
         tsgDBL SinDR, tsgDBL CosDR );
/* Rotate camera along 'Right' direction */
VOID TSG_CameraRotateByRight( tsgCAMERA *Cam,
         tsgDBL SinDU, tsgDBL CosDU );

/*** Rotation around camera 'look at' point ***/
/* Rotate camera around camera 'look at' point by vertical
 * direction */
VOID TSG_CameraRotateLookAtVertical( tsgCAMERA *Cam,
         tsgDBL SinDU, tsgDBL CosDU );
/* Rotate camera around camera 'look at' point by horizontal
 * direction */
VOID TSG_CameraRotateLookAtHorizontal( tsgCAMERA *Cam,
         tsgDBL SinDR, tsgDBL CosDR );

/***
 * Utility functions
 ***/

/* Calculation invertse kinematics of two linked sticks by
 * specified length of every part and end position */
BOOL TSG_IK2( BOOL IsAntiClockWise,
         tsgDBL L1, tsgDBL L2, tsgDBL X, tsgDBL Y,
         tsgDBL *SinA1, tsgDBL *CosA1,
         tsgDBL *SinA2, tsgDBL *CosA2 );

#endif /* _TSGRAPH_H_ */

/* END OF 'TSGRAPH.H' FILE */
