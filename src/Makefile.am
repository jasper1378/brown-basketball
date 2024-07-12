AM_CXXFLAGS = -std=c++20
bin_PROGRAMS = brown-basketball
brown_basketball_SOURCES = \
	analysis1.cpp      \
	analysis1.hpp      \
	analysis2.cpp      \
	analysis2.hpp      \
	common.hpp         \
	database.cpp       \
	database.hpp       \
	generation.cpp     \
	generation.hpp     \
	main.cpp           \
	my_random.cpp      \
	my_random.hpp      \
	printing1.cpp      \
	printing1.hpp      \
	printing2.cpp      \
	printing2.hpp      \
	scoring.cpp        \
	scoring.hpp        \
	user_settings.hpp
brown_basketball_CPPFLAGS = -I$(top_srcdir)/deps/bits-and-bytes/include -I$(top_srcdir)/deps/libconfigfile/include
brown_basketball_LDADD = $(top_builddir)/deps/libconfigfile/src/libconfigfile.la
