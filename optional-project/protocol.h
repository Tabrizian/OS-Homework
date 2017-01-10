/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _PROTOCOL_H_RPCGEN
#define _PROTOCOL_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct date {
	char *format;
};
typedef struct date date;

#define DATETIME 0x2fffffff
#define DATETIME_1 1

#if defined(__STDC__) || defined(__cplusplus)
#define ADD 1
extern  int * add_1(date *, CLIENT *);
extern  int * add_1_svc(date *, struct svc_req *);
extern int datetime_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define ADD 1
extern  int * add_1();
extern  int * add_1_svc();
extern int datetime_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_date (XDR *, date*);

#else /* K&R C */
extern bool_t xdr_date ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_PROTOCOL_H_RPCGEN */