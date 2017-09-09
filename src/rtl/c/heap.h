#pragma once

#ifdef __cplusplus
extern "C" {
#endif

Object g2rtl_SI_alloc_primitive_vector(SI_Dimension numelems,
										enum SI_gcls etype);

void g2rtl_init_heaps();

#ifdef __cplusplus
}
#endif
