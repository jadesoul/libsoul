#ifndef FILESYS_H_1356524201_83
#define FILESYS_H_1356524201_83
/**
 * File: filesys.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 20:16:41.833000
 * Written In: Peking University, beijing, China
 */

#include <corelib.h>


#ifdef OS_WIN32
	class path {
	private:
		str p;
		WIN32_FIND_DATAA* pwfd;
		HANDLE hFind;
		bool updated;
	public:
		inline path(const char* s="."):p(s), pwfd(0), hFind(INVALID_HANDLE_VALUE), updated(false) {}
		inline path(const string& s):p(s), pwfd(0), hFind(INVALID_HANDLE_VALUE), updated(false) {}
		inline path(const str& s):p(s), pwfd(0), hFind(INVALID_HANDLE_VALUE), updated(false) {}
		inline path(const path& r):p(r.p), pwfd(0), hFind(INVALID_HANDLE_VALUE), updated(false) {}
		
		inline path& operator +=(const path& r) { return add(r); }
		inline path operator +(const path& r) { return clone()+=r; }
		
		inline path& operator +=(str r) { return add(r); }
		inline path operator +(str r) { return clone()+=r; }
		
		inline path& operator /=(const path& r) { return join(r); }
		inline path operator /(const path& r) { return clone()/=r; }
		
		inline path& operator /=(str r) { return join(path(r)); }
		inline path operator /(str r) { return clone()/=r; }
		
		inline path& operator /=(const char* r) { return join(path(r)); }
		inline path operator /(const char* r) { return clone()/=r; }
		
		inline operator str() { return p; }
		friend inline ostream& operator<<(ostream& o, path& p) { return o<<p.p; }
		
		inline ~path() { free(); }
		
		inline path clone();
		inline path& add(const path& r);
		inline path& join(const path& r);
		
		inline const string tostr() const;
		inline const char* tocstr() const;
		
		const bool exists();
		const bool isfile();
		const bool isdir();
		inline const bool isnfile() { return !isfile(); }
		inline const bool isndir() { return !isdir(); }
		const ulong fsize();
		const list<ushort> fctime();
		const list<ushort> fmtime();
		const list<ushort> fatime();
		list<str> files(const str& pattern="*.*");
		list<str> dirs(const str& pattern="*.*");
		list<str> items(const str& pattern="*.*");
		list<str> split() const;
		list<str> splitdir() const;
		list<str> splitext() const;
		str dirname() const;
		str extension() const;
		str filename() const;
		
		template<class walker>
		void walk(const walker& w) {
			travel(w);
		}
		
		void walk();
		
	private:
		template<class walker>
		void travel(const walker& w, uint d=0) {
			list<str> files=this->files();
			list<str> dirs=this->dirs();
			w(p, dirs, files, d);
			uint l=dirs.size();
			for_n(i, l) clone().join(dirs[i]).travel(w, d+1);
		}
		
		const list<ushort> ftime2list(FILETIME& ftime);
		inline const bool valid(HANDLE& h) { return h!=INVALID_HANDLE_VALUE; }
		inline const bool find_valid() { return valid(hFind); }
		void free();
		void update();
	};
	
#else

	class path {
	private:
		str p;
		struct stat* pst;
		bool updated;	//is the stat updated
		bool valid;	//is this a valid path
	public:
		inline path(const str& s="."):p(s), pst(NULL), updated(false), valid(false) {}
		
		inline ~path() { free(); }
		
		inline path& operator +=(const path& r) { return add(r); }
		inline path operator +(const path& r) const { return clone()+=r; }
		
		// inline path& operator +=(const str& r) { return add(r); }
		// inline path operator +(const str& r) const { return clone()+=r; }
		
		inline path& operator /=(const path& r) { return join(r); }
		inline path operator /(const path& r) const { return clone()/=r; }
		
		// inline path& operator /=(const str& r) { return join(path(r)); }
		// inline path operator /(const str& r) const { return clone()/=r; }
		
        inline path& operator /=(const char* r) { return join(path(r)); }
		inline path operator /(const char* r) const { return clone()/=r; }
		friend inline ostream& operator<<(ostream& o, path& p) { return o<<p.p; }
		
		inline path clone() const { return path(p); }
		path& add(const path& r);
		path& join(const path& r);
		
		inline const string tostr() const { return p.tostr(); }
		inline const char* tocstr() const { return p.tocstr(); }
		
		const bool exists() const;
		const bool isfile(const bool refresh=false);
		const bool isdir(const bool refresh=false);
		const bool isnfile();
		const bool isndir();
		const ulong fsize(const bool refresh=false);
		const long fmtime(const bool refresh=false);
		const long fatime(const bool refresh=false);
		const long fctime(const bool refresh=false);
		list<str> files();
		list<str> dirs();
		list<str> items();
		list<str> split() const;
		list<str> splitdir() const;
		list<str> splitext() const;
		str dirname() const;
		str extension() const;
		str filename() const;
		
	private:
		void free();
		void update();
	};
	
#endif

#if defined(OS_WIN32)

	// get current work dir
	// DWORD GetCurrentDirectory(
	// DWORD nBufferLength, // size of directory buffer
	// LPTSTR lpBuffer // directory buffer
	// );
	inline str cwd() {
		char buf[1024];
		return str(buf, buf+GetCurrentDirectory(1024, buf));
	}

	// copy a file from src to dst
	// BOOL CopyFile(LPCTSTR lpExistingFileName,LPCTSTR lpNewFileName,BOOL bFailIfExists );
	inline const bool cp(const char* src, const char* dst) {
		return CopyFile(src, dst, 1);
	}

	// move a file or dir from src to dst
	// BOOL MoveFile(
		// LPCTSTR lpExistingFileName, // file name or dir name
		// LPCTSTR lpNewFileName // new file name or dir name
	// );
	inline const bool mv(const char* src, const char* dst) {
		return MoveFile(src, dst);
	}

	// delete a file
	// BOOL DeleteFile(LPCTSTR lpFileName);
	inline const bool rm(const char* p) {
		return DeleteFile(p);
	}

	// delete a dir
	// BOOL RemoveDirectory(LPCTSTR lpPathName);
	inline const bool rd(const char* p) {
		return RemoveDirectory(p);
	}

	// make a dir
	// BOOL CreateDirectory(LPCTSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes );
	inline const bool md(const char* p) {
		return CreateDirectory(p, NULL);
	}

	// make a dir, auto make dirs if parent not exist
	const bool mds(const char* p);

	// recursively delete a dir
	const bool rds(const char* p);

#elif defined(OS_LINUX)

	// get current work dir
	str cwd();
	
	// copy a file from src to dst
	const bool cp(const char* src, const char* dst);
	inline const bool cp(const str& src, const str& dst) { return cp(src.tocstr(), dst.tocstr()); }
	
	// move a file or dir from src to dst
	inline const bool mv(const char* src, const char* dst) {
		return 0==rename(src, dst);
	}
	inline const bool mv(const str& src, const str& dst) { return mv(src.tocstr(), dst.tocstr()); }
	
	// delete a file
	inline const bool rm(const char* p) {
		// return 0==remove(p.tocstr());
		return 0==unlink(p);
	}
	inline const bool rm(const path& p) { return rm(p.tocstr()); }
	
	// delete a dir, the dir should be empty
	inline const bool rd(const char* p) {
		return 0==rmdir(p);
	}
	inline const bool rd(const path& p) { return rd(p.tocstr()); }
	
	// make a dir
	inline const bool md(const char* p) {
		return 0==mkdir(p, S_IRWXU);
	}
	inline const bool md(const path& p) { return md(p.tocstr()); }
	
	// make a dir, auto make dirs if parent not exist
	const bool mds(const char* p);
	inline const bool mds(const path& p) { return mds(p.tocstr()); }
	
	// recursively delete a dir
	const bool rds(const char* p);
	inline const bool rds(const path& p) { return rds(p.tocstr()); }
	
	
#elif defined(OS_OSX)
#endif

class file {
private:
	FILE* fp;
	str fn;
	//modes: rt wt at rb wb ab rt+ wt+ at+ rb+ wb+ ab+
	str m;
	char* buf;
	//forbidden copy and assign
	file(const file& r) {}
	inline file& operator=(const file& r) { return *this; }
public:
	file(const path& filename, const str& mode="rt");
	inline const bool notend() const { return !feof(fp); }
	inline file& flush() { fflush(fp); return *this; }
	str read(uint size=0);
	str readline();
	list<str> readlines();
	file& write(const str& s);
	file& writeline(const str& s);
	file& writelines(list<str> lst);
	~file();
private:
	inline const bool opened() const { return fp!=NULL; }
	file& close();
	inline void check_buf() { if (!buf) buf=new char[64*1024+1]; }
};

str fread(const path& p, const bool binary=false);
uint fwrite(const str& s, const path& p, const bool append=false, const bool binary=false);

#undef ENDL
#undef SLASH


#endif /* FILESYS_H_1356524201_83 */
