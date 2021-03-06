/*
 * Socket union header.
 * Copyright (c) 1997 Kunihiro Ishiguro
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.  
 */

#ifndef _SOCKUNION_H_
#define _SOCKUNION_H_

#if 0
union sockunion {
  struct sockinet {
    u_char si_len;
    u_char si_family;
    u_short si_port;
  } su_si;
  struct sockaddr_in  su_sin;
  struct sockaddr_in6 su_sin6;
};
#define su_len                su_si.si_len
#define su_family     su_si.si_family
#define su_port               su_si.si_port
#endif /* 0 */

union sockunion 
{
  struct sockaddr sa;
  struct sockaddr_in sin;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 sin6;
#endif /* ENABLE_IPV6 */
};

enum connect_result
{
  connect_error,
  connect_success,
  connect_in_progress
};

/* Default address family. */
#ifdef ENABLE_IPV6
#define AF_INET_UNION AF_INET6
#else
#define AF_INET_UNION AF_INET
#endif

/* Sockunion address string length.  Same as INET6_ADDRSTRLEN. */
#define SU_ADDRSTRLEN 46

/* Macro to set link local index to the IPv6 address.  For KAME IPv6
   stack. */
#ifdef KAME
#define	IN6_LINKLOCAL_IFINDEX(a)  ((a).s6_addr[2] << 8 | (a).s6_addr[3])
#define SET_IN6_LINKLOCAL_IFINDEX(a, i) \
  do { \
    (a).s6_addr[2] = ((i) >> 8) & 0xff; \
    (a).s6_addr[3] = (i) & 0xff; \
  } while (0)
#else
#define	IN6_LINKLOCAL_IFINDEX(a)
#define SET_IN6_LINKLOCAL_IFINDEX(a, i)
#endif /* KAME */

/* shortcut macro to specify address field of struct sockaddr */
#define sock2ip(X)   (((struct sockaddr_in *)(X))->sin_addr.s_addr)
#ifdef ENABLE_IPV6
#define sock2ip6(X)  (((struct sockaddr_in6 *)(X))->sin6_addr.s6_addr)
#endif /* ENABLE_IPV6 */

#define sockunion_family(X)  (X)->sa.sa_family

/* Prototypes. */
#if (!defined __SOCKUNION_C)
#define EXT extern
#else
#define EXT
#endif
EXT int str2sockunion (const char *, union sockunion *);
EXT const char *sockunion2str (union sockunion *, char *, size_t);
EXT int sockunion_cmp (union sockunion *, union sockunion *);
EXT int sockunion_same (union sockunion *, union sockunion *);
EXT char *sockunion_su2str (union sockunion *);
EXT union sockunion *sockunion_str2su (const char *);
EXT struct in_addr sockunion_get_in_addr (union sockunion *);
EXT int sockunion_accept (int sock, union sockunion *);
EXT int sockunion_stream_socket (union sockunion *);
EXT int sockopt_reuseaddr (int);
EXT int sockopt_reuseport (int);
EXT int sockunion_bind (int sock, union sockunion *, unsigned short, union sockunion *);
EXT int sockopt_ttl (int, int, int);
EXT int sockopt_minttl (int, int, int);
EXT int sockopt_cork (int, int);
EXT int sockunion_socket (union sockunion *);
EXT const char *inet_sutop (union sockunion *, char *);
EXT enum connect_result sockunion_connect (int, union sockunion *, unsigned short, unsigned int);
EXT union sockunion *sockunion_getsockname (int);
EXT union sockunion *sockunion_getpeername (int);
EXT union sockunion *sockunion_dup (union sockunion *);
EXT void sockunion_free (union sockunion *);
#undef EXT

#endif /* _SOCKUNION_H_ */
