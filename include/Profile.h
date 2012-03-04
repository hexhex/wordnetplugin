#ifndef _PROFILE_H
#define _PROFILE_H

#ifdef PROFILE
# ifdef HAVE_TIME_H
#  include <time.h>
# else
#  error time.h is required for profiling. Run configure without --enable-profile.
# endif
# define START_TIMING clock_t _start_time = clock(); cout.precision(5);
# define END_TIMING(str)  cout << "P> wordnet-atom: " << str << " in " << (((double) (clock() - _start_time)) / CLOCKS_PER_SEC) << " seconds" << endl;
#else
# define START_TIMING ;
# define END_TIMING(str) ;
#endif

#endif
