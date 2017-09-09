/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      icmp.h
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   yduJ
 +
 + Description: Windows include files do not provide the structures and
 +		definitions for IP/ICMP headers.  Cribbed these from the web 
 +              (http://www.winsock2.org/samples/Ch05/Ping/PING.H),
 +		but then worried about copyright and messed with names,
 +		comments, and formatting.
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



#define ICMP_ECHOREPLY	0
#define ICMP_ECHO	8
#define ICMP_TIMXCEED  11

#if defined(WIN32)

// IP header
struct ip
{
	unsigned int ip_hl:4;           // length of the header
	unsigned int version:4;         // IP version
	u_char	ip_tos;			// type of service
	short	ip_len;			// total length
	short	ip_id;			// ID
	short	ip_off;		        // flags and fragment offset
	u_char	ip_ttl;			// time to live
	u_char	ip_p;  		        // protocol
	u_short	ip_sum;		        // checksum
	struct	in_addr ip_src;	        // internet address - source
	struct	in_addr ip_dst;	        // internet address - destination
};

#endif

// ICMP header
struct icmp
{
	u_char	icmp_type;              // type
	u_char	icmp_code;              // code
	u_short	icmp_cksum;		// checksum
	u_short	icmp_id;		// identification
	u_short	icmp_seq;		// sequence
	char	icmp_data;		// data
};


