/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <fnordmetric/io/file.h>
#include <fnordmetric/util/buffer.h>
#include <fnordmetric/util/runtimeexception.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace fnord {
namespace io {

File File::openFile(
    const std::string& filename,
    int flags) {
  int open_flags = 0;

  switch (flags & (O_READ | O_WRITE)) {
    case O_READ:
      open_flags = O_RDONLY;
      break;

    case O_WRITE:
      open_flags = O_WRONLY;
      break;

    case (O_READ | O_WRITE):
      open_flags = O_RDWR;
      break;

    default:
      RAISE(
          kIllegalArgumentError,
          "openFile('%s'): at least one of O_READ | O_WRITE must be set",
          filename.c_str());
  }

  if ((flags & O_CREATEOROPEN) > 0) {
    open_flags |= O_CREAT;
  } else if ((flags & O_CREATE) > 0) {
    open_flags |= O_CREAT;
    open_flags |= O_EXCL;
  }

  if ((flags & O_TRUNCATE) > 0) {
    open_flags |= O_TRUNC;
  }

  int fd = open(filename.c_str(), open_flags, S_IRUSR | S_IWUSR);
  if (fd < 0) {
    RAISE_ERRNO(kIOError, "openFile('%s'): open() failed", filename.c_str());
  }

  if ((flags & O_AUTODELETE) > 0) {
    unlink(filename.c_str());
  }

  return File(fd);
}

File::File(int fd) : fd_(fd) {}

File::~File() {
  if (fd_ >= 0) {
    close(fd_);
  }
}

File::File(File&& other) : fd_(other.fd_) {
  other.fd_ = -1;
}

int File::fd() const {
  return fd_;
}

size_t File::size() const {
  struct stat fd_stat;

  if (fstat(fd_, &fd_stat) < 0) {
    RAISE_ERRNO(kIOError, "fstat(%i) failed", fd_);
  }

  return fd_stat.st_size;
}

void File::seekTo(size_t pos) {
  if (lseek(fd_, pos, SEEK_SET) < 0) {
    RAISE_ERRNO(kIOError, "lseek(%i) failed", fd_);
  }
}

size_t File::read(void* buf, size_t buf_len) {
  int res = ::read(fd_, buf, buf_len);

  if (res < 0) {
    RAISE_ERRNO(kIOError, "read(%i) failed", fd_);
  }

  return res;
}

size_t File::read(util::Buffer* buf) {
  return read(buf->data(), buf->size());
}

File File::clone() const {
  int new_fd = dup(fd_);

  if (new_fd < 0) {
    RAISE_ERRNO(kIOError, "dup(%i) failed", fd_);
  }

  return File(new_fd);
}

}
}
