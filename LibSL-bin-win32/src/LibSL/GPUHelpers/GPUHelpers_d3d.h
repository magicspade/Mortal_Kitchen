/* --------------------------------------------------------------------
Author: Sylvain Lefebvre    sylvain.lefebvre@sophia.inria.fr

                  Simple Library for Graphics (LibSL)

This software is a computer program whose purpose is to offer a set of
tools to simplify programming real-time computer graphics applications
under OpenGL and DirectX.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.
-------------------------------------------------------------------- */
// ------------------------------------------------------
// LibSL::GPUHelpers_d3d
// ------------------------------------------------------
//
// GPU helpers Direct3D policies
// 
// ------------------------------------------------------
// Sylvain Lefebvre - 2006-06-05
// ------------------------------------------------------

#pragma once

#include <LibSL/GPUHelpers/GPUHelpers.h>
#include <LibSL/D3DHelpers/D3DHelpers.h>

#include <dxut.h>

// ------------------------------------------------------

namespace LibSL {
  namespace GPUHelpers {

#ifdef DIRECT3D

    class OcclusionQuery_D3D9_Policy
    {
    public:

      typedef IDirect3DQuery9* t_Handle;

      static t_Handle create()
      {
        t_Handle q;
        LPDIRECT3DDEVICE9 d3d = LIBSL_DIRECT3D_DEVICE;
        d3d->CreateQuery(D3DQUERYTYPE_OCCLUSION, &q);
        return (q);
      }

      static void destroy(t_Handle& q)
      {
        LIBSL_D3D_SAFE_RELEASE(q);
      }

      static void start(const t_Handle& q)
      {
        q->Issue(D3DISSUE_BEGIN);
      }

      static void stop(const t_Handle& q)
      {
        q->Issue(D3DISSUE_END);
      }

      static int done(const t_Handle& q)
      {
        DWORD numdrawn=0;
        HRESULT ready=q->GetData(&numdrawn,sizeof(DWORD),D3DGETDATA_FLUSH);
        if (ready == S_FALSE) {
          return (-1);
        } else {
          return int(numdrawn);
        }
      }

    };

    typedef OcclusionQuery_generic<OcclusionQuery_D3D9_Policy> OcclusionQuery;
    typedef OcclusionQuery::t_AutoPtr                          OcclusionQuery_Ptr;

#endif

#ifdef DIRECTX10

    // TODO

#endif

  } //namespace LibSL::GPUHelpers
} //namespace LibSL

// ------------------------------------------------------
