////////////////////////////////////////////////////////
//	CRAP Library
//!		@file compilers.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Looking for compiler specific macros.
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_COMPILERS_H
#define CRAP_CONFIG_COMPILERS_H

//lib namespace
namespace crap
{

/*
 *! @brief enum representing found compiler
 */

enum compiler_type
{
	gcc,
	vc,
	borland,
	intel,
	unknown_compiler
};

// GCC macro
#if ( defined(__GNUC__) )

//#define CRAP_COMPILER_GCC
#define CRAP_COMPILER_NAME "GCC"
#define CRAP_INLINE __inline__
#define CRAP_CPP __cplusplus
#define CRAP_TEMPLATE_CONST_FIX
static const crap::compiler_type compiler = gcc;

// VC macro
#elif ( defined(_MSC_VER) )

#define CRAP_COMPILER_VC
#define CRAP_COMPILER_NAME "VC++"
#define CRAP_INLINE __inline
#define CRAP_CPP __cplusplus
#define CRAP_TEMPLATE_CONST_FIX const
static const crap::compiler_type compiler = vc;

// borland macro
#elif ( defined(__BORLANDC__) )

#define CRAP_COMPILER_BORLAND
#define CRAP_COMPILER_NAME "Borland C++"
#define CRAP_INLINE inline
#define CRAP_CPP __cplusplus
#define CRAP_TEMPLATE_CONST_FIX
static const crap::compiler_type compiler = borland;

// intel compiler
#elif ( defined(__ICL) || defined(__ICC) )

#define CRAP_COMPILER_INTEL
#define CRAP_COMPILER_NAME "Intel C++"
#define CRAP_INLINE inline
#define CRAP_CPP __cplusplus
#define CRAP_TEMPLATE_CONST_FIX
static const crap::compiler_type compiler = intel;

// other compiler
#else

#define CRAP_COMPILER_UNKNOWN
#define CRAP_COMPILER_NAME "Unknown"
#define CRAP_INLINE
#define CRAP_CPP
#define CRAP_TEMPLATE_CONST_FIX
static const crap::compiler_type compiler = UnknownCompiler;

#endif

}	// namespace crap

#endif // CRAP_CONFIG_COMPILERS_H
