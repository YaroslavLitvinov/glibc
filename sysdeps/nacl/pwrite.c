/* Copyright (C) 1991, 1995, 1996, 1997, 1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <errno.h>
#include <unistd.h>

#include "zrt.h" //__nacl_irt_pwrite

/* Write NBYTES of BUF to FD at given position OFFSET without changing
   the file position.  Return the number written, or -1.  */
ssize_t
__libc_pwrite (int fd, const void *buf, size_t nbytes, off_t offset)
{
  if (nbytes == 0)
    return 0;
  if (fd < 0)
    {
      __set_errno (EBADF);
      return -1;
    }
  if (buf == NULL || offset < 0)
    {
      __set_errno (EINVAL);
      return -1;
    }

  size_t nwrote;
  int result = __nacl_irt_pwrite(fd, buf, nbytes, offset, &nwrote );
  if (result != 0)
      return -1;
  else
      return nwrote;
}
strong_alias (__libc_pwrite, __pwrite)
weak_alias (__libc_pwrite, pwrite)
