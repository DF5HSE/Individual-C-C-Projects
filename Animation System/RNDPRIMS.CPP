/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : RNDPRIMS.CPP
 * PURPOSE      : Render system.
 *                Primitives class implementation module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "anim.h"
#include "rndprims.h"

/* Default primitve class constructor.
 * ARGUMENTS: None.
 */
figl::prims::prims(VOID)
{
}

/* Primitive class destructor.
 * ARGUMENTS: None.
 */
figl::prims::~prims(VOID)
{
  for (auto it = Prims.begin(); it != Prims.end(); ++it)
    delete *it;
}

/* Load primitives function.
 * ARGUMENTS:
 *   - file name:
 *       const std::string &FileName;
 *   - transformation matrix:
 *       const mth::matr<FLT> &Transform;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL figl::prims::Load( const std::string &FileName, const mth::matr<FLT> &Transform )
{
  FILE *F;
  DWORD Sign;
  INT NoofP = 0, NoofM = 0, NoofT = 0, i;

  /* Open file */
  if ((F = fopen(FileName.c_str(), "rb")) == NULL)
    return FALSE;
  /* Check signature */
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3DM")
  {
    fclose(F);
    return FALSE;
  }

  /* Read quantities */
  fread(&NoofP, 4, 1, F);
  fread(&NoofM, 4, 1, F);
  fread(&NoofT, 4, 1, F);

  Prims.resize(NoofP);

  /* Primitive material indices */
  std::vector<INT> prims_mtl;
  prims_mtl.resize(NoofP);

  /* Load primitives */
  for (i = 0; i < NoofP; i++)
  {
    INT nv = 0, ni = 0, j;
    std::vector<figl::prim::VERTEX> V;
    std::vector<INT> I;

    fread(&nv, 4, 1, F);
    fread(&ni, 4, 1, F);
    fread(&prims_mtl[i], 4, 1, F);
    V.resize(nv);
    I.resize(ni);

    fread(&V[0], 1, sizeof(prim::VERTEX) * nv, F);
    fread(&I[0], 1, sizeof(INT) * ni, F);

    for (j = 0; j < nv; j++)
    {
      V[j].P = Transform.PointTransform(V[j].P);
      V[j].N = Transform.NormalTransform(V[j].N);
    }
    Prims[i] = new prim(prim::MESH, V, I);
  }

  /* Load materials */
    struct STORE_MATERIAL
    {
      CHAR Name[300]; /* Material name */
  
                      /* Illumination coefficients */
      vec Ka, Kd, Ks;        /* Ambient, diffuse, specular coefficients */
      FLT Ph;                /* Phong power coefficient */
      FLT Trans;             /* Transparency factor */
      INT Tex[8];            /* Texture references */
  
                             /* Shader string */
      CHAR ShaderStr[300];
      INT Shader;                        /* Texture references */
    }; /* End of 'STORE_MATERIAL' struct */

    std::vector<material *> mtls;
    std::vector<STORE_MATERIAL> store_mtls;
    mtls.resize(NoofM);
    store_mtls.resize(NoofM);
    if (NoofM > 0)
    {
      fread(&store_mtls[0], sizeof(STORE_MATERIAL), NoofM, F);
      for (INT i = 0; i < NoofM; i++)
        mtls[i] = anim::GetInstance().Materials.Create(store_mtls[i].Name,
          store_mtls[i].Ka, store_mtls[i].Kd, store_mtls[i].Ks,
          store_mtls[i].Ph, store_mtls[i].Trans);
    }
    /* Load textures */
    std::vector<texture *> texs;
    texs.resize(NoofT);
    for (i = 0; i < NoofT; i++)
    {
      CHAR Name[300];
      INT W, H, C;
      BYTE *mem;

      fread(Name, 1, 300, F);
      fread(&W, 4, 1, F);
      fread(&H, 4, 1, F);
      fread(&C, 4, 1, F);
      mem = new BYTE[W * H * C];
      fread(mem, C, W * H, F);
      texs[i] = anim::GetInstance().Textures.Create(Name, W, H, C, mem);
      delete[] mem;
    }
    fclose(F);

    /* Correct material texture references */
    for (INT i = 0; i < NoofM; i++)
      for (INT t = 0; t < 8; t++)
        if (store_mtls[i].Tex[t] != -1)
          mtls[i]->Tex[t] = texs[store_mtls[i].Tex[t]];

    /* Correct primitives material references */
    for (INT i = 0; i < NoofP; i++)
      if (prims_mtl[i] != -1)
        Prims[i]->Mtl = mtls[prims_mtl[i]];
      else
        Prims[i]->Mtl = nullptr;

  return TRUE;
} /* End of 'figl::prims::Load' function */

/* END OF 'RNDPRIMS.H' FILE */