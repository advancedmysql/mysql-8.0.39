/*
  Copyright (c) 2022, 2024, Oracle and/or its affiliates.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License, version 2.0,
  as published by the Free Software Foundation.

  This program is designed to work with certain software (including
  but not limited to OpenSSL) that is licensed under separate terms,
  as designated in a particular file or component or in included license
  documentation.  The authors of MySQL hereby grant you an additional
  permission to link the program and your derivative works with the
  separately licensed software that they have either included with
  the program or referenced in the documentation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "rest_signal_abort.h"

#include <csignal>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif
#include "mysqlrouter/rest_api_utils.h"

constexpr const char RestSignalAbort::path_regex[];

bool RestSignalAbort::on_handle_request(HttpRequest &req,
                                        const std::string & /* base_path */,
                                        const std::vector<std::string> &) {
  if (!ensure_no_params(req)) return true;

#ifdef _WIN32
  RaiseException(EXCEPTION_ACCESS_VIOLATION, EXCEPTION_NONCONTINUABLE, 0, NULL);
#else
  raise(SIGSEGV);
#endif

  return true;
}