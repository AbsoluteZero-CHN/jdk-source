/*
 * Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef OS_WINDOWS_VM_DECODER_WINDOWS_HPP
#define OS_WINDOWS_VM_DECIDER_WINDOWS_HPP

#include <windows.h>
#include <imagehlp.h>

#include "utilities/decoder.hpp"

// functions needed for decoding symbols
typedef DWORD (WINAPI *pfn_SymSetOptions)(DWORD);
typedef BOOL  (WINAPI *pfn_SymInitialize)(HANDLE, PCTSTR, BOOL);
typedef BOOL  (WINAPI *pfn_SymGetSymFromAddr64)(HANDLE, DWORD64, PDWORD64, PIMAGEHLP_SYMBOL64);
typedef DWORD (WINAPI *pfn_UndecorateSymbolName)(const char*, char*, DWORD, DWORD);

class WindowsDecoder: public NullDecoder {

public:
  WindowsDecoder();
  ~WindowsDecoder() { uninitialize(); };

  bool can_decode_C_frame_in_vm() const;
  bool demangle(const char* symbol, char *buf, int buflen);
  bool decode(address addr, char *buf, int buflen, int* offset, const char* modulepath = NULL);

private:
  void initialize();
  void uninitialize();

private:
  HMODULE                   _dbghelp_handle;
  bool                      _can_decode_in_vm;
  pfn_SymGetSymFromAddr64   _pfnSymGetSymFromAddr64;
  pfn_UndecorateSymbolName  _pfnUndecorateSymbolName;
};

#endif // OS_WINDOWS_VM_DECODER_WINDOWS_HPP

