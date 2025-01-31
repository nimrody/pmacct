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

/* prototypes */
#if !defined(__BMP_UTIL_C)
#define EXT extern
#else
#define EXT
#endif
EXT char *bmp_get_and_check_length(char **, u_int32_t *, u_int32_t);
EXT int bmp_get_tlv_and_check_length(char **, u_int32_t *, struct bmp_rm_tlv *);
EXT void bmp_jump_offset(char **, u_int32_t *, u_int32_t);
EXT u_int32_t bmp_packet_adj_offset(char *, u_int32_t, u_int32_t, u_int32_t, char *);
EXT void bmp_link_misc_structs(struct bgp_misc_structs *);
EXT struct bgp_peer *bmp_sync_loc_rem_peers(struct bgp_peer *, struct bgp_peer *);
EXT int bmp_peer_init(struct bmp_peer *, int);
EXT void bmp_peer_close(struct bmp_peer *, int);
EXT int bmp_tlv_array_increment(int, int);
EXT char *bmp_tlv_type_print(u_int16_t, const char *, const char **, int);
EXT char *bmp_term_reason_print(u_int16_t);

EXT void bgp_peer_log_msg_extras_bmp(struct bgp_peer *, int, void *);
EXT void bgp_peer_logdump_initclose_extras_bmp(struct bgp_peer *, int, void *);

EXT void bgp_msg_data_set_data_bmp(struct bmp_chars *, struct bmp_data *);
EXT int bgp_extra_data_cmp_bmp(struct bgp_msg_extra_data *, struct bgp_msg_extra_data *);
EXT int bgp_extra_data_process_bmp(struct bgp_msg_extra_data *, struct bgp_info *);
EXT void bgp_extra_data_free_bmp(struct bgp_msg_extra_data *);
EXT void bgp_extra_data_print_bmp(struct bgp_msg_extra_data *, int, void *);
#undef EXT
