/* PipeWire */
/* SPDX-FileCopyrightText: Copyright © 2023 Wim Taymans <wim.taymans@gmail.com> */
/* SPDX-License-Identifier: MIT */

#ifndef PIPEWIRE_RTP_STREAM_H
#define PIPEWIRE_RTP_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

struct rtp_stream;

#define DEFAULT_FORMAT		"S16BE"
#define DEFAULT_RATE		48000
#define DEFAULT_CHANNELS	2
#define DEFAULT_POSITION	"[ FL FR ]"

#define ERROR_MSEC		2.0f
#define DEFAULT_SESS_LATENCY	100.0f

#define DEFAULT_MTU		1280
#define DEFAULT_MIN_PTIME	2.0f
#define DEFAULT_MAX_PTIME	20.0f

struct rtp_stream_events {
#define RTP_VERSION_STREAM_EVENTS        0
	uint32_t version;

	void (*destroy) (void *data);

	void (*state_changed) (void *data, bool started, const char *error);

	void (*param_changed) (void *data, uint32_t id, const struct spa_pod *param);

	void (*send_packet) (void *data, struct iovec *iov, size_t iovlen);

	void (*send_feedback) (void *data, uint32_t seqnum);
};

struct rtp_stream *rtp_stream_new(struct pw_core *core,
		enum pw_direction direction, struct pw_properties *props,
		const struct rtp_stream_events *events, void *data);

void rtp_stream_destroy(struct rtp_stream *s);

int rtp_stream_update_properties(struct rtp_stream *s, const struct spa_dict *dict);

int rtp_stream_receive_packet(struct rtp_stream *s, uint8_t *buffer, size_t len);

uint64_t rtp_stream_get_time(struct rtp_stream *s, uint64_t *rate);

uint16_t rtp_stream_get_seq(struct rtp_stream *s);

void rtp_stream_set_first(struct rtp_stream *s);

enum pw_stream_state rtp_stream_get_state(struct rtp_stream *s, const char **error);

int rtp_stream_set_param(struct rtp_stream *s, uint32_t id, const struct spa_pod *param);

int rtp_stream_update_params(struct rtp_stream *stream,
			const struct spa_pod **params,
			uint32_t n_params);

#ifdef __cplusplus
}
#endif

#endif /* PIPEWIRE_RTP_STREAM_H */
