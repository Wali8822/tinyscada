


#if defined(__USE_SELECT)

typedef struct elApiData {
	fd_set rset, wset;
} elApiData;


OD_RET elApiCreate(elEventLoop *el) {
	elApiData * state = (elApiData*)malloc(sizeof(elApiData));

	if (!state) { return OD_FAILURE; }

	FD_ZERO(&state->rset);
	FD_ZERO(&state->wset);

	el->api_data = state;

	return OD_SUCCESS;
}

OD_VOID elApiDestroy(elEventLoop *el) {
	free(el->api_data);
}

OD_RET elApiAddEvent(elEventLoop *el, OD_I32 fd, OD_U16 mask) {
	elApiData *state = el->api_data;

	if(mask & ELF_READ)	{ FD_SET(fd, &state->rset); }
	if(mask & ELF_WRITE) { FD_SET(fd, &state->wset); }

	return OD_SUCCESS;
}

OD_VOID elApiDelEvent(elEventLoop *el, OD_I32 fd, OD_U16 mask) {
	elApiData *state = el->api_data;

	if (mask & ELF_READ) { FD_CLR(fd, &state->rset); }
	if (mask & ELF_WRITE) { FD_CLR(fd, &state->wset); }
}

OD_I32 elApiPoll (elEventLoop *el, struct timeval *tvp) {
	elApiData *state = el->api_data;
	OD_I32 numEvents = 0;
	OD_I32 ret, ix;
	OD_U16 mask;
	fd_set _rset, _wset;

	memcpy(&_rset, &state->rset, sizeof(fd_set));
	memcpy(&_wset, &state->wset, sizeof(fd_set));

	ret = select(el->maxfd, &_rset, &_wset, NULL, tvp);

	if(ret > 0) {
		for(ix = 0; ix <= el->maxfd; ++ix) {
			elFileEvent *fe = &el->events[ix];
			mask = ELF_NONE;

			if(fe->mask == ELF_NONE) { continue; }

			if((fe->mask & ELF_READ) && (FD_ISSET(ix, &_rset))) { mask |= ELF_READ; }
			if((fe->mask & ELF_WRITE) && (FD_ISSET(ix, &_wset))) { mask |= ELF_WRITE; }

			if(mask != ELF_NONE) {
				el->fireds[numEvents].fd = ix;
				el->fireds[numEvents].mask = mask;
				++numEvents;
			}
		}
	}

	return numEvents;
}

#endif
