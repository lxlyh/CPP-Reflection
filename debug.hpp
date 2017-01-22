/*
* Copyright (C) 2016 Vladimir Antonyan <antony_v@outlook.com>
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*/

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <cassert>

#define DEBUG_BUILD

#ifdef DEBUG_BUILD
#define ASSERT( x ) assert( x )
#else 
#define ASSERT ( x ) (void)sizeof( x );
#endif // DEBUG_BUILD

#endif // DEBUG_HPP