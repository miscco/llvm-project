(*===-- llvm_vectorize.ml - LLVM OCaml Interface --------------*- OCaml -*-===*
 *
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 *===----------------------------------------------------------------------===*)

external add_loop_vectorize
  : [<Llvm.PassManager.any] Llvm.PassManager.t -> unit
  = "llvm_add_loop_vectorize"
external add_slp_vectorize
  : [<Llvm.PassManager.any] Llvm.PassManager.t -> unit
  = "llvm_add_slp_vectorize"
