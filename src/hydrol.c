#include "pihm.h"

void Hydrol (pihm_struct pihm)
{
    int             i;

    /*
     * Determine source of ET
     */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (i = 0; i < nelem; i++)
    {
        elem_struct *elem;

        elem = &pihm->elem[i];

        /* Source of direct evaporation */
#ifdef _NOAH_
        if (elem->ws.gw > elem->soil.depth - elem->soil.dinf)
        {
            elem->wf.edir_surf = 0.0;
            elem->wf.edir_unsat = 0.0;
            elem->wf.edir_gw = elem->wf.edir;
        }
        else
        {
            elem->wf.edir_surf = 0.0;
            elem->wf.edir_unsat = elem->wf.edir;
            elem->wf.edir_gw = 0.0;
        }
#else
        if (elem->ws.surf >= DEPRSTG)
        {
            elem->wf.edir_surf = elem->wf.edir;
            elem->wf.edir_unsat = 0.0;
            elem->wf.edir_gw = 0.0;
        }
        else if (elem->ws.gw > elem->soil.depth - elem->soil.dinf)
        {
            elem->wf.edir_surf = 0.0;
            elem->wf.edir_unsat = 0.0;
            elem->wf.edir_gw = elem->wf.edir;
        }
        else
        {
            elem->wf.edir_surf = 0.0;
            elem->wf.edir_unsat = elem->wf.edir;
            elem->wf.edir_gw = 0.0;
        }
#endif

        /* Source of transpiration */
#ifdef _NOAH_
        elem->ps.gwet = GWTransp (elem->wf.ett, elem->wf.et, elem->ps.nwtbl,
            elem->ps.nroot);
        elem->wf.ett_unsat = (1.0 - elem->ps.gwet) * elem->wf.ett;
        elem->wf.ett_gw = elem->ps.gwet * elem->wf.ett;
#else
        if (elem->ws.gw > elem->soil.depth - elem->ps.rzd)
        {
            elem->wf.ett_unsat = 0.0;
            elem->wf.ett_gw = elem->wf.ett;
        }
        else
        {
            elem->wf.ett_unsat = elem->wf.ett;
            elem->wf.ett_gw = 0.0;
        }
#endif
    }

    /*
     * Water flow
     */
    VerticalFlow (pihm);

    LateralFlow (pihm);

    RiverFlow (pihm);
}
