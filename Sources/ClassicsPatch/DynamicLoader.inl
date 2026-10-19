/* Copyright (c) 2026 Dreamy Cecil
This program is free software; you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License as published by
the Free Software Foundation


This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#include <ClassicsPatchAPI/include/classicspatch_api.h>

static ClassicsPatchGlobalFunctions _patch;
static bool _bClassicsPatchLoaded = false;

static IClassicsPatchAPI *_pAPI = NULL;

static void LoadClassicsPatch(void) {
  // Load the library to begin with
  HMODULE hCore = LoadLibraryA("ClassicsCore.dll");
  if (hCore == NULL) return;

  // Hook up its functions and verify patch version
  if (ClassicsPatch_GetGlobalFunctionsFromModule(&_patch)) {
    _bClassicsPatchLoaded = (_patch._Verify(NULL) == k_EVerifyAPIResult_OK);
  }
};

static void LoadClassicsPatchVirtualAPI(void) {
  CShellSymbol_ *pssAPI = _pShell_GetSymbol_(CTString("ClassicsPatchAPI"), TRUE);
  _pAPI = (pssAPI != NULL ? (IClassicsPatchAPI *)*CShellSymbol_ss_pvValue(pssAPI) : NULL);
};
