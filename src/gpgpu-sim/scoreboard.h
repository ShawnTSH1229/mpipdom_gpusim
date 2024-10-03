// Copyright (c) 2009-2011, Tor M. Aamodt, Inderpreet Singh
// The University of British Columbia
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution. Neither the name of
// The University of British Columbia nor the names of its contributors may be
// used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <stdio.h>
#include <stdlib.h>
#include <map> //GPGPULearning:ZSY_MPIPDOM
#include <set>
#include <vector>
#include "assert.h"

#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "../abstract_hardware_model.h"

class Scoreboard {
 public:
  Scoreboard(unsigned sid, unsigned n_warps, class gpgpu_t *gpu);

  void reserveRegisters(const warp_inst_t *inst);
  void releaseRegisters(const warp_inst_t *inst);
  void releaseRegister(unsigned wid, active_mask_t i_mask/*GPGPULearning:ZSY_MPIPDOM*/, unsigned regnum);

  bool checkCollision(unsigned wid, active_mask_t msk/*GPGPULearning:ZSY_MPIPDOM*/, const inst_t *inst) const;
  bool pendingWrites(unsigned wid) const;
  void printContents() const;
  const bool islongop(unsigned warp_id, unsigned regnum);

 private:
  void reserveRegister(unsigned wid, active_mask_t i_mask/*GPGPULearning:ZSY_MPIPDOM*/, unsigned regnum);
  int get_sid() const { return m_sid; }

  unsigned m_sid;

  // keeps track of pending writes to registers
  // indexed by warp id, reg_id => pending write count

  //GPGPULearning:ZSY_MPIPDOM:[BEGIN]

  // A form of set-associative look-up table (Figure 8a) is employed, where sets are indexed using warp
  // ids and entries within each set contain a destination register ID of an instruction in flight for a given wa
  //std::vector<std::set<unsigned> > reg_table;
  
  //Therefore, we modify the scoreboard design by adding a reserved mask (R-mask) field to each entry in the scoreboard look-up table as shown in Figure 8b
  std::vector<std::map<unsigned, active_mask_t> > reg_table;
  //GPGPULearning:ZSY_MPIPDOM:[END]

  // Register that depend on a long operation (global, local or tex memory)
  std::vector<std::set<unsigned> > longopregs;

  class gpgpu_t *m_gpu;
};

#endif /* SCOREBOARD_H_ */
