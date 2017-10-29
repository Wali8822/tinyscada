

#if defined(WIN32)

	#ifdef RDBCLI_EXPORTS
		#define RDB_CLIENT_API __declspec(dllexport)
	#else
		#define RDB_CLIENT_API __declspec(dllimport)
	#endif

#endif
