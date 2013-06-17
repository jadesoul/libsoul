/**
 * File: filesys.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 20:16:43.981000
 * Written In: Peking University, beijing, China
 */

#include "filesys.h"

#if defined(OS_WIN32)
	// #define ENDL "\r\n"
	#define ENDL "\n"
	#define SLASH "\\"
#elif defined(OS_LINUX)
	#define ENDL "\n"
	#define SLASH "/"
#elif defined(OS_OSX)
	#define ENDL "\r"
	#define SLASH "/"
#else
	#define ENDL "\n"
	#define SLASH "/"
#endif

class walker {
public:
	inline void operator()(const str& root, const list<str>& dirs, const list<str>& files, const uint depth) const {
		str prefix=str("\t")*depth;
		uint l=files.size();
		for_n(i, l) cout<<prefix<<"- "<<files[i]<<endl;
		l=dirs.size();
		for_n(i, l) cout<<prefix<<"+ "<<dirs[i]<<endl;
	}
};


#ifdef OS_WIN32

	inline path path::clone() { 
		return path(p); 
	}
	inline path& path::add(const path& r) { 
		updated=false;
		p+=r.p; 
		return *this; 
	}
	inline path& path::join(const path& r) {
		updated=false;
		const str& q=r.p;
		if (p.size()==0 OR q.size()==0) {
			p+=q;
			return *this;
		}
		char a='\\', b='/';
		char sep=a;
		char x=p[-1], y=q[0];
		if ((x==a OR x==b) AND (y==a OR y==b))  p=p(0, -1)+sep+q(1);
		else if ((x==a OR x==b) AND (y!=a AND y!=b))  p=p(0, -1)+sep+q;
		else if ((x!=a AND x!=b) AND (y==a OR y==b))  p=p+sep+q(1);
		else p=p+sep+q;
		return *this;
	}

	inline const string path::tostr() const { return p.tostr(); }
	inline const char* path::tocstr() const { return p.tocstr(); }

	const bool path::exists() {
		update();
		return find_valid();
	}
	const bool path::isfile() {
		update();
		return find_valid() AND !(pwfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	}
	const bool path::isdir() {
		update();
		return find_valid() AND (pwfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	}

	const ulong path::fsize() {
		update();
		return (pwfd->nFileSizeHigh * (ulong(MAXDWORD)+1)) + pwfd->nFileSizeLow;
	}
	const list<ushort> path::fctime() {
		update();
		return ftime2list(pwfd->ftCreationTime);
	}
	const list<ushort> path::fmtime() {
		update();
		return ftime2list(pwfd->ftLastWriteTime);
	}
	const list<ushort> path::fatime() {
		update();
		return ftime2list(pwfd->ftLastAccessTime);
	}
	list<str> path::files(const str& pattern) {
		str old=p;
		if (NOT isdir()) p=dirname();
		join(pattern);
		updated=false;
		update();
		list<str> fns;
		if (find_valid()) {
			do {
				if (!(pwfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					const char* fname=(const char*)pwfd->cFileName;
					fns.append(fname);
				}
			}
			while (FindNextFileA(hFind, pwfd));
		}
		p=old;
		updated=false;
		return fns;
	}
	list<str> path::dirs(const str& pattern) {
		str old=p;
		if (NOT isdir()) p=dirname();
		join(pattern);
		updated=false;
		update();
		list<str> fns;
		if (find_valid()) {
			do {
				if (pwfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					const char* fname=(const char*)pwfd->cFileName;
					if (strcmp(fname, "." )!=0 AND strcmp(fname, ".." )!=0) fns.append(fname);
				}
			}
			while (FindNextFileA(hFind, pwfd));
		}
		p=old;
		updated=false;
		return fns;
	}
	list<str> path::items(const str& pattern) {
		str old=p;
		if (NOT isdir()) p=dirname();
		join(pattern);
		updated=false;
		update();
		list<str> fns;
		if (find_valid()) {
			do {
				const char* fname=(const char*)pwfd->cFileName;
				if (pwfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					if (strcmp(fname, "." )!=0 AND strcmp(fname, ".." )!=0) fns.append(fname);
				} else {
					fns.append(fname);
				}
			}
			while (FindNextFileA(hFind, pwfd));
		}
		p=old;
		updated=false;
		return fns;
	}
	list<str> path::split() const {
		int a=p.rfind("/"), b=p.rfind("\\"), c=max(a, b);
		str dp, fn, name, ext;
		if (c==-1) {
			dp=".";
			fn=p;
		} else {
			dp=p(0, c);
			fn=p(c+1);
		}
		c=fn.rfind(".");
		if (c==-1) {
			name=fn;
			ext="";
		} else {
			name=fn(0, c);
			ext=fn(c);
		}
		return list<str>(p, dp, fn, name, ext);
	}
	list<str> path::splitdir() const {
		int a=p.rfind("/"), b=p.rfind("\\"), c=max(a, b);
		list<str> rets;
		if (c==-1) {
			rets.append(".");
			rets.append(p);
		} else {
			rets.append(p(0, c));
			rets.append(p(c+1));
		}
		return rets;
	}
	list<str> path::splitext() const {
		int c=p.rfind(".");
		list<str> rets;
		if (c==-1) {
			rets.append(p);
			rets.append("");
		} else {
			rets.append(p(0, c));
			rets.append(p(c));
		}
		return rets;
	}
	str path::dirname() const {
		int a=p.rfind("/"), b=p.rfind("\\"), c=max(a, b);
		return (c==-1)?".":p(0, c);
	}
	str path::extension() const {
		str fn=filename();
		int a=fn.rfind(".");
		return (a==-1)?"":fn(a);
	}
	str path::filename() const {
		int a=p.rfind("/"), b=p.rfind("\\"), c=max(a, b);
		return (c==-1)?p:p(c+1);
	}


	void path::walk() {
		travel(walker());
	}

	const list<ushort> path::ftime2list(FILETIME& ftime) {
		TIME_ZONE_INFORMATION zoneinfo;
		GetTimeZoneInformation(&zoneinfo);
		SYSTEMTIME greenwichsystime, localtime;
		FileTimeToSystemTime(&ftime, &greenwichsystime);
		SystemTimeToTzSpecificLocalTime(&zoneinfo, &greenwichsystime, &localtime);
		ushort& year=localtime.wYear, &month=localtime.wMonth, &day=localtime.wDay, 
			&hour=localtime.wHour, &min=localtime.wMinute, &sec=localtime.wSecond,
			&msec=localtime.wMilliseconds;
		return list<ushort>(year, month, day, hour, min, sec, msec);
	}
	
	
	void path::free() {
		if (find_valid()) FindClose(hFind);
		if (pwfd) {
			delete pwfd;
			pwfd=NULL;
		}
	}
	void path::update() {
		if (!updated) {
			free();
			pwfd=new WIN32_FIND_DATAA;
			assert(pwfd);
			hFind=FindFirstFileA(tocstr(), pwfd);
			updated=true;
		}
	}

		
#else

	path& path::add(const path& r) {
		updated=false;
		p+=r.p; return *this; 
	}
	
	path& path::join(const path& r) {
		updated=false;
		const str& q=r.p;
		if (p.size()==0 OR q.size()==0) {
			p+=q;
			return *this;
		}
		char a='\\', b='/';
		char sep=b;
		char x=p[-1], y=q[0];
		if ((x==a OR x==b) AND (y==a OR y==b))  p=p(0, -1)+sep+q(1);
		else if ((x==a OR x==b) AND (y!=a AND y!=b))  p=p(0, -1)+sep+q;
		else if ((x!=a AND x!=b) AND (y==a OR y==b))  p=p+sep+q(1);
		else p=p+sep+q;
		return *this;
	}
	
	// inline const string path::tostr() const { return p.tostr(); }
	// inline const char* path::tocstr() const { return p.tocstr(); }
	
	const bool path::exists() const {
		return 0==access(p.tocstr(), F_OK);
	}
	const bool path::isfile(const bool refresh) {
		if (!updated OR refresh) update();
		return valid AND (S_IFREG == (pst->st_mode & S_IFMT));
	}
	const bool path::isdir(const bool refresh) {
		if (!updated OR refresh) update();
		return valid AND (S_IFDIR == (pst->st_mode & S_IFMT));
	}
	
	const bool path::isnfile() { return !isfile(); }
	const bool path::isndir() { return !isdir(); }
	
	const ulong path::fsize(const bool refresh) {
		if (!updated OR refresh) update();
		assert(valid);
		return pst->st_size;
	}
	const long path::fmtime(const bool refresh) {
		if (!updated OR refresh) update();
		assert(valid);
		return pst->st_mtime;
	}
	const long path::fatime(const bool refresh) {
		if (!updated OR refresh) update();
		assert(valid);
		return pst->st_atime;
	}
	const long path::fctime(const bool refresh) {
		if (!updated OR refresh) update();
		assert(valid);
		return pst->st_ctime;
	}
	
	list<str> path::files() {
		str old=p;
		if (NOT isdir()) p=dirname();
		const char* dir=p.tocstr();
		list<str> rets;
		//const char *pth=p.tocstr();
		char *buf=new char[p.size()+300];
		struct dirent *ent;
		DIR *d;
		struct stat st;
		if (NULL==(d=opendir(dir))) return rets;
		while ( (ent=readdir(d)) ) {
			if (0==strcmp("..", ent->d_name) OR 0==strcmp(".", ent->d_name)) continue;
			sprintf(buf, "%s/%s", dir, ent->d_name);
			// printf("path=%s\n", ptr);
			stat(buf, &st);
			if (S_IFREG == (st.st_mode & S_IFMT)) rets.append(ent->d_name);
		}
		closedir(d);
		delete[] buf;
		p=old;
		return rets;
	}
	list<str> path::dirs() {
		str old=p;
		if (NOT isdir()) p=dirname();
		const char* dir=p.tocstr();
		list<str> rets;
		//const char *pth=p.tocstr();
		char *buf=new char[p.size()+300];
		struct dirent *ent;
		DIR *d;
		struct stat st;
		if (NULL==(d=opendir(dir))) return rets;
		while ( (ent=readdir(d)) ) {
			if (0==strcmp("..", ent->d_name) OR 0==strcmp(".", ent->d_name)) continue;
			sprintf(buf, "%s/%s", dir, ent->d_name);
			// printf("path=%s\n", ptr);
			stat(buf, &st);
			if (S_IFDIR == (st.st_mode & S_IFMT)) rets.append(ent->d_name);
		}
		closedir(d);
		delete[] buf;
		p=old;
		return rets;
	}
	list<str> path::items() {
		str old=p;
		if (NOT isdir()) p=dirname();
		const char* dir=p.tocstr();
		list<str> rets;
		//const char *pth=p.tocstr();
		char *buf=new char[p.size()+300];
		struct dirent *ent;
		DIR *d;
		//struct stat st;
		if (NULL==(d=opendir(dir))) return rets;
		while ( (ent=readdir(d)) ) {
			if (0==strcmp("..", ent->d_name) OR 0==strcmp(".", ent->d_name)) continue;
			sprintf(buf, "%s/%s", dir, ent->d_name);
			// printf("path=%s\n", ptr);
			rets.append(ent->d_name);
		}
		closedir(d);
		delete[] buf;
		p=old;
		return rets;
	}
	
	list<str> path::split() const {
		int c=p.rfind("/");
		str dp, fn, name, ext;
		if (c==-1) {
			dp=".";
			fn=p;
		} else {
			dp=p(0, c);
			fn=p(c+1);
		}
		c=fn.rfind(".");
		if (c==-1) {
			name=fn;
			ext="";
		} else {
			name=fn(0, c);
			ext=fn(c);
		}
		return list<str>(p, dp, fn, name, ext);
	}
	list<str> path::splitdir() const {
		int c=p.rfind("/");
		list<str> rets;
		if (c==-1) {
			rets.append(".");
			rets.append(p);
		} else {
			rets.append(p(0, c));
			rets.append(p(c+1));
		}
		return rets;
	}
	list<str> path::splitext() const {
		int c=p.rfind(".");
		list<str> rets;
		if (c==-1) {
			rets.append(p);
			rets.append("");
		} else {
			rets.append(p(0, c));
			rets.append(p(c));
		}
		return rets;
	}
	str path::dirname() const {
		int c=p.rfind("/");
		return (c==-1)?".":p(0, c);
	}
	str path::extension() const {
		str fn=filename();
		int a=fn.rfind(".");
		return (a==-1)?"":fn(a);
	}
	str path::filename() const {
		int c=p.rfind("/");
		return (c==-1)?p:p(c+1);
	}
	
	void path::free() {
		if (pst) {
			delete pst;
			pst=NULL;
		}
	}
	void path::update() {
		free();
		pst=new struct stat;
		assert(pst);
		valid=(0==stat(p.tocstr(), pst));
		updated=true;
	}
	
#endif

#if defined(OS_WIN32)

	// make a dir, auto make dirs if parent not exist
	const bool mds(const char* p) {
		path parent(path(p).dirname());
		if (parent.isndir() AND !mds(parent.tocstr()))  return false;
		return md(p); 
	}

	// recursively delete a dir
	const bool rds(const char* p) {
		path top(p);
		if (top.isndir()) return false;
		list<str> files=top.files();
		uint l=files.size();
		for_n(i, l) if (!rm((top / files[i]).tocstr())) return false;
		list<str> dirs=top.dirs();
		l=dirs.size();
		for_n(i, l) if (!rds((top / dirs[i]).tocstr())) return false;
		return rd(p);
	}

#elif defined(OS_LINUX)

	// get current work dir
	str cwd() {
		char localbuf[MAXPATHLEN+1];
		char *ret=getcwd(localbuf, MAXPATHLEN);
		if (ret==NULL) {
			errno = EACCES; /* Most likely error */
			return "";
		}
		return str(localbuf);
	}
	
	// copy a file from src to dst
	const bool cp(const char* src, const char* dst) {
		const static int BUFFER_SIZE=1024;
		int from_fd, to_fd;
		int bytes_read, bytes_write;
		char buffer[BUFFER_SIZE];
		char *ptr;

		if ((from_fd=open(src, O_RDONLY))==-1) {
			fprintf(stderr,"Open %s Error:%s\n", src, strerror(errno));
			return false;
		}

		if ((to_fd=open(dst, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR))==-1) {
			fprintf(stderr,"Open %s Error:%s\n", dst, strerror(errno));
			return false;
		}
		
		bool success=true;
		while ( (bytes_read=read(from_fd, buffer, BUFFER_SIZE)) ) {
			if ((bytes_read==-1) && (errno!=EINTR)) {
				success=false;
				break;
			} else if (bytes_read>0) {
				ptr=buffer;
				while ( (bytes_write=write(to_fd, ptr, bytes_read)) ) {
					if ((bytes_write==-1) && (errno!=EINTR)) {
						success=false;
						break;
					} else if (bytes_write==bytes_read) break;
					else if (bytes_write>0) {
						ptr+=bytes_write;
						bytes_read-=bytes_write;
					}
				}
				if (bytes_write==-1)break;
			}
		}
		close(from_fd);
		close(to_fd);
		return success;
	}

	// make a dir, auto make dirs if parent not exist
	const bool mds(const char* p) {
		path parent(path(p).dirname());
		if (parent.isndir() AND !mds(parent.tocstr()))  return false;
		return md(p);
	}

	// recursively delete a dir
	const bool rds(const char* p) {
		path top(p);
		if (top.isndir()) return false;
		list<str> files=top.files();
		uint l=files.size(); 
		for_n(i, l) if (!rm((top / files[i]).tocstr())) return false;
		list<str> dirs=top.dirs();
		l=dirs.size();
		for_n(i, l) if (!rds((top / dirs[i]).tocstr())) return false;
		return rd(p);
	}
	
#elif defined(OS_OSX)
#endif

file::file(const path& filename, const str& mode):fp(0), fn(filename.tostr()), m(mode), buf(0) {
	fp=fopen(fn.tocstr(), m.tocstr());
	if (fp==NULL) {
		cout<<"Could not open file:"<<fn<<" with mode:"<<m;
		exit(1);
	}
}

str file::read(uint size) {
	assert(opened());
	if (size==0) {
		fseek(fp, 0, SEEK_END);
		size=ftell(fp);
		rewind(fp);
	}
	char* buffer=new char[size];
	if (buffer==NULL) {
		fputs("Memory error: No buffer for read", stderr);
		exit(2);
	}
	str s(buffer, buffer+fread(buffer, 1, size, fp));
	delete buffer;
	return s;
}
str file::readline() {
	assert(opened());
	check_buf();
	string ret;
	if (fgets(buf, 64*1024+1, fp)) ret=buf;
	uint l=ret.size();
	if (l>=2 AND ret[l-2]=='\r' AND ret[l-1]=='\n') return str(ret.begin(), ret.end()-2);
	if (l>=1 AND ret[l-1]=='\n') return str(ret.begin(), ret.end()-1);
	return ret;
}
list<str> file::readlines() {
	list<str> rets;
	while (notend()) rets.append(readline());
	return rets;
}

file& file::write(const str& s) {
	assert(opened());
	uint l=s.size();
	if (l==0) return *this;
	fwrite(s.tocstr(), 1, l, fp);
	return *this;
}
file& file::writeline(const str& s) {
	write(s);
	fputs(ENDL, fp);
	return *this;
}
file& file::writelines(list<str> lst) {
	uint l=lst.size();
	for_n(i, l) writeline(lst[i]);
	return *this;
}

file::~file() {
	flush().close();
	delete buf;
}

file& file::close() {
	if (fp) fclose(fp);
	fp=NULL;
	return *this; 
}

str fread(const path& p, const bool binary) {
	FILE* fp;
	uint size;
	char* buf;
	fp=fopen(p.tocstr(), binary?"rb":"rt");
	assert(fp);//File error: Could not open file for read
	fseek(fp, 0, SEEK_END);
	size=ftell(fp);
	if (size==0) {
		fclose(fp);
		return "";
	}
	rewind(fp);
	buf=new char[size];
	assert(buf);//Memory error: Could not allocate buffer for read
	size=fread(buf, 1, size, fp);
	fclose(fp);
	str ret(buf, buf+size);
	delete buf;
	return ret;
}

uint fwrite(const str& s, const path& p, const bool append, const bool binary) {
	FILE* fp;
	uint size=s.size();
	const char* buf=s.tocstr();
	fp=fopen(p.tocstr(), append?(binary?"ab":"at"):(binary?"wb":"wt"));
	assert(fp);//File error: Could not open file for write
	size=fwrite(buf, 1, size, fp);
	fclose(fp);
	return size;
}

#undef ENDL
#undef SLASH
