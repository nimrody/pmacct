/*
    pmacct (Promiscuous mode IP Accounting package)
    pmacct is Copyright (C) 2003-2019 by Paolo Lucente
*/

/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/* includes */

/* defines */
#define BMP_TCP_PORT		1790
#define BMP_MAX_PEERS_DEFAULT	4
#define BMP_V3			3

#define BMP_MISSING_PEER_UP_LOG_TOUT	60

/* BMP message types */
#define BMP_MSG_ROUTE_MONITOR		0	
#define	BMP_MSG_STATS			1
#define BMP_MSG_PEER_DOWN		2
#define BMP_MSG_PEER_UP			3
#define	BMP_MSG_INIT			4
#define BMP_MSG_TERM			5
#define BMP_MSG_ROUTE_MIRROR		6	
#define BMP_MSG_TLV_RM_ADJ_RIB_IN	7 /* draft-hsmit-bmp-extensible-routemon-msgs-00 */
#define BMP_MSG_TLV_RM_ADJ_RIB_OUT	8 /* draft-hsmit-bmp-extensible-routemon-msgs-00 */
#define BMP_MSG_TLV_RM_LOC_RIB		9 /* draft-hsmit-bmp-extensible-routemon-msgs-00 */
#define BMP_MSG_TYPE_MAX		9 /* set to the highest BMP_MSG_* value */

static const char *bmp_msg_types[] = {
  "Route Monitoring",
  "Statistics Report",
  "Peer Down Notification",
  "Peer Up Notification",
  "Initiation Message",
  "Termination Message",
  "Route Mirroring",
  "TLV RM Adj-Rib-In",
  "TLV RM Adj-Rib-Out",
  "TLV RM Loc-Rib"
};

struct bmp_common_hdr {
  u_char	version;
  u_int32_t	len;
  u_char	type;
} __attribute__ ((packed));

#define BMP_PEER_TYPE_GLOBAL	0
#define BMP_PEER_TYPE_L3VPN	1
#define BMP_PEER_TYPE_LOCAL	2
#define BMP_PEER_TYPE_LOC_RIB	3 /* draft-evens-grow-bmp-local-rib-01 */ 
#define BMP_PEER_TYPE_MAX	3 /* set to the highest BMP_PEER_TYPE_* value */

static const char *bmp_peer_types[] = {
  "Global Instance Peer",
  "RD Instance Peer",
  "Local Instance Peer",
  "Loc-RIB Instance Peer"
};

#define BMP_PEER_FLAGS_ARI_V	0x80
#define BMP_PEER_FLAGS_ARI_L	0x40
#define BMP_PEER_FLAGS_ARI_A	0x20

#define BMP_PEER_FLAGS_LR_F	0x80 /* draft-ietf-grow-bmp-local-rib-01 */

#define BMP_PEER_FLAGS_ARO_O	0x10 /* draft-ietf-grow-bmp-adj-rib-out-01 */

struct bmp_peer_hdr {
  u_char	type;
  u_char	flags;
  u_char	rd[RD_LEN];
  u_int32_t	addr[4];
  u_int32_t	asn;
  u_int32_t	bgp_id;
  u_int32_t	tstamp_sec;
  u_int32_t	tstamp_usec;
} __attribute__ ((packed));

struct bmp_tlv_hdr {
  u_int16_t     type;
  u_int16_t     len;
} __attribute__ ((packed));

#define BMP_INIT_INFO_STRING	0
#define BMP_INIT_INFO_SYSDESCR	1
#define BMP_INIT_INFO_SYSNAME	2
#define BMP_INIT_INFO_MAX	2

#define BMP_INIT_INFO_ENTRIES	8

static const char *bmp_init_info_types[] = {
  "string",
  "sysdescr",
  "sysname"  
};

#define BMP_TERM_INFO_STRING    0
#define BMP_TERM_INFO_REASON	1
#define BMP_TERM_INFO_MAX	1

#define BMP_TERM_INFO_ENTRIES	8

#define BMP_TERM_REASON_ADM	0
#define BMP_TERM_REASON_UNK	1
#define BMP_TERM_REASON_OOR	2
#define BMP_TERM_REASON_DUP	3
#define BMP_TERM_REASON_PERM	4
#define BMP_TERM_REASON_MAX	4 /* set to the highest BMP_TERM_* value */

static const char *bmp_term_info_types[] = {
  "string",
  "reason"
};

static const char *bmp_term_reason_types[] = {
  "Session administratively closed",
  "Unspecified reason",
  "Out of resources",
  "Redundant connection",
  "Session permanently administratively closed"
};

struct bmp_stats_hdr {
  u_int32_t	count;
} __attribute__ ((packed));

/* draft-hsmit-bmp-extensible-routemon-msgs-00: start */
struct bmp_rm_tlv {
  u_int16_t	type;
  u_int16_t 	len;
  void *	value;
};

#define BGP_MONITOR_TYPE_UPDATE			1 
#define BGP_MONITOR_TYPE_FLAGS			2

#define BGP_MONITOR_FLAG_MIN_LEN		2

/* first byte */
#define BGP_MONITOR_FLAG_PRE_POLICY		0x01
#define BGP_MONITOR_FLAG_POST_POLICY		0x02
#define BGP_MONITOR_FLAG_ROUTE_VALID		0x04
#define BGP_MONITOR_FLAG_ROUTE_INVALID		0x08
#define BGP_MONITOR_FLAG_ROUTE_ACCEPT		0x10
#define BGP_MONITOR_FLAG_ROUTE_REJECT		0x20
#define BGP_MONITOR_FLAG_ROUTE_BEST		0x40
#define BGP_MONITOR_FLAG_ROUTE_NOT_BEST		0x80

/* second byte */
#define BGP_MONITOR_FLAG_ROUTE_GLOBAL		0x01
#define BGP_MONITOR_FLAG_ROUTE_NOT_GLOBAL	0x02
#define BGP_MONITOR_FLAG_AS_PATH_4B		0x04
#define BGP_MONITOR_FLAG_RESERVED1		0x08
#define BGP_MONITOR_FLAG_NLRI_PATH_ID		0x10
#define BGP_MONITOR_FLAG_NLRI_NO_PATH_ID	0x20
#define BGP_MONITOR_FLAG_ROUTE_GLOBAL_BEST	0x40
#define BGP_MONITOR_FLAG_ROUTE_GLOBAL_NO_BEST	0x80
/* draft-hsmit-bmp-extensible-routemon-msgs-00: end */

struct bmp_peer {
  struct bgp_peer self;
  void *bgp_peers;
  struct log_notification missing_peer_up;
};

#define BMP_STATS_TYPE0		0  /* (32-bit Counter) Number of prefixes rejected by inbound policy */
#define BMP_STATS_TYPE1		1  /* (32-bit Counter) Number of (known) duplicate prefix advertisements */
#define BMP_STATS_TYPE2		2  /* (32-bit Counter) Number of (known) duplicate withdraws */
#define BMP_STATS_TYPE3		3  /* (32-bit Counter) Number of updates invalidated due to CLUSTER_LIST loop */
#define BMP_STATS_TYPE4		4  /* (32-bit Counter) Number of updates invalidated due to AS_PATH loop */
#define BMP_STATS_TYPE5		5  /* (32-bit Counter) Number of updates invalidated due to ORIGINATOR_ID */ 
#define BMP_STATS_TYPE6		6  /* (32-bit Counter) Number of updates invalidated due to AS_CONFED loop */
#define BMP_STATS_TYPE7		7  /* (64-bit Gauge) Number of routes in Adj-RIB-In */
#define BMP_STATS_TYPE8		8  /* (64-bit Gauge) Number of routes in Loc-RIB */
#define BMP_STATS_TYPE9		9  /* (64-bit Gauge) Number of routes in per-AFI/SAFI Abj-RIB-In */
#define BMP_STATS_TYPE10	10 /* (64-bit Gauge) Number of routes in per-AFI/SAFI Loc-RIB */
#define BMP_STATS_TYPE11	11 /* (32-bit Counter) Number of updates subjected to treat-as-withdraw */ 
#define BMP_STATS_TYPE12	12 /* (32-bit Counter) Number of prefixes subjected to treat-as-withdraw */
#define BMP_STATS_TYPE13	13 /* (32-bit Counter) Number of duplicate update messages received */

/* Types 14-17 defined in draft-evens-grow-bmp-adj-rib-out-01 */
#define BMP_STATS_TYPE14	14 /* (64-bit Gauge) Number of routes in Adj-RIBs-Out Pre-Policy */
#define BMP_STATS_TYPE15	15 /* (64-bit Gauge) Number of routes in Adj-RIBs-Out Post-Policy */
#define BMP_STATS_TYPE16	16 /* (64-bit Gauge) Number of routes in per-AFI/SAFI Abj-RIB-Out */
#define BMP_STATS_TYPE17	17 /* (64-bit Gauge) Number of routes in per-AFI/SAFI Abj-RIB-Out */
#define BMP_STATS_MAX		17 /* set to the highest BMP_STATS_* value */

static const char *bmp_stats_cnt_types[] = {
  "Number of prefixes rejected by inbound policy",
  "Number of (known) duplicate prefix advertisements",
  "Number of (known) duplicate withdraws",
  "Number of updates invalidated due to CLUSTER_LIST loop",
  "Number of updates invalidated due to AS_PATH loop",
  "Number of updates invalidated due to ORIGINATOR_ID",
  "Number of updates invalidated due to AS_CONFED loop",
  "Number of routes in Adj-RIBs-In",
  "Number of routes in Loc-RIB",
  "Number of routes in per-AFI/SAFI Abj-RIB-In",
  "Number of routes in per-AFI/SAFI Loc-RIB",
  "Number of updates subjected to treat-as-withdraw",
  "Number of prefixes subjected to treat-as-withdraw",
  "Number of duplicate update messages received",
  "Number of routes in Adj-RIBs-Out Pre-Policy",
  "Number of routes in Adj-RIBs-Out Post-Policy",
  "Number of routes in per-AFI/SAFI Abj-RIB-Out Pre-Policy",
  "Number of routes in per-AFI/SAFI Abj-RIB-Out Post-Policy"
};

struct bmp_stats_cnt_hdr {
  u_int16_t	type;
  u_int16_t	len;
} __attribute__ ((packed));

#define BMP_PEER_UP_INFO_ENTRIES	8	

#define BMP_PEER_DOWN_RESERVED		0
#define BMP_PEER_DOWN_LOC_NOT_MSG	1
#define BMP_PEER_DOWN_LOC_CODE		2
#define BMP_PEER_DOWN_REM_NOT_MSG	3
#define BMP_PEER_DOWN_REM_CODE		4
#define BMP_PEER_DOWN_DECFG		5
#define BMP_PEER_DOWN_MAX		5 /* set to the highest BMP_PEER_DOWN_* value */

static const char *bmp_peer_down_reason_types[] = {
  "Reserved",
  "The local system closed the session",
  "The local system closed the session without a notification message",
  "The remote system closed the session",
  "The remote system closed the session without a notification message",
  "Info for this peer will no longer be sent for configuration reasons"
};

struct bmp_peer_down_hdr {
  u_char	reason;
} __attribute__ ((packed));

struct bmp_peer_up_hdr {
  u_int32_t	loc_addr[4];
  u_int16_t	loc_port;
  u_int16_t	rem_port;
  /* Sent OPEN Message */
  /* Received OPEN Message */
} __attribute__ ((packed));

struct bmp_chars {
  u_int8_t peer_type;
  u_int8_t is_post;
  u_int8_t is_2b_asn;
  u_int8_t is_filtered;
  u_int8_t is_out;
  u_int8_t is_loc;
}; 

struct bmp_data {
  u_int8_t family;
  struct host_addr peer_ip;
  struct host_addr bgp_id;
  u_int32_t peer_asn;
  struct bmp_chars chars;
  struct timeval tstamp;
};

/* more includes */
#include "bmp_logdump.h"
#include "bmp_msg.h"
#include "bmp_util.h"
#include "bmp_lookup.h"

/* prototypes */
#if !defined(__BMP_C)
#define EXT extern
#else
#define EXT
#endif
EXT void nfacctd_bmp_wrapper();
EXT void skinny_bmp_daemon();
EXT void bmp_prepare_thread();
EXT void bmp_prepare_daemon();
#undef EXT

/* global variables */
#if (!defined __BMP_C)
#define EXT extern
#else
#define EXT
#endif
EXT struct bmp_peer *bmp_peers;
EXT u_int32_t (*bmp_route_info_modulo)(struct bgp_peer *, path_id_t *, int);
EXT struct bgp_rt_structs *bmp_routing_db;
EXT struct bgp_misc_structs *bmp_misc_db;
#undef EXT
