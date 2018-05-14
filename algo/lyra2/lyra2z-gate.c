#include "lyra2z-gate.h"
#include "lyra2.h"

void lyra2z_set_target( struct work* work, double job_diff )
{
 work_set_target( work, job_diff / (256.0 * opt_diff_factor) );
}

bool register_lyra2z_algo( algo_gate_t* gate )
{
#if defined(LYRA2Z_8WAY)
  gate->miner_thread_init = (void*)&lyra2z_8way_thread_init;
  gate->scanhash   = (void*)&scanhash_lyra2z_8way;
  gate->hash       = (void*)&lyra2z_8way_hash;
#elif defined(LYRA2Z_4WAY)
  gate->miner_thread_init = (void*)&lyra2z_4way_thread_init;
  gate->scanhash   = (void*)&scanhash_lyra2z_4way;
  gate->hash       = (void*)&lyra2z_4way_hash;
#else
  gate->miner_thread_init = (void*)&lyra2z_thread_init;
  gate->scanhash   = (void*)&scanhash_lyra2z;
  gate->hash       = (void*)&lyra2z_hash;
#endif
  gate->optimizations = SSE42_OPT | AVX2_OPT;
//  gate->optimizations = EMPTY_SET;
//#ifdef __SSE2__
//  gate->optimizations |= SSE2_OPT;
//#endif
//#ifdef __AES__
//  gate->optimizations |= AES_OPT;
//#endif
//#ifdef __SSE4_2__
//  gate->optimizations |= SSE42_OPT;
//#endif
//#ifdef __AVX__
//  gate->optimizations |= AVX_OPT;
//#endif
//#ifdef __AVX2__
//  gate->optimizations |= AVX2_OPT;
//#endif
//#ifdef __SHA__
//  gate->optimizations |= SHA_OPT;
//#endif
//#ifdef __AVX512F__
//  gate->optimizations |= AVX512_OPT;
//#endif
  gate->get_max64  = (void*)&get_max64_0xffffLL;
  gate->set_target = (void*)&lyra2z_set_target;
  return true;
};

