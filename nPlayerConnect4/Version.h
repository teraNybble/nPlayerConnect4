#ifndef VERSION_H
#define VERSION_H

struct Version{
	Version() { ver = verMinor = verMajor = 0; }
	Version(int ver, int major, int minor) {
		this->ver = ver;
		verMajor = major;
		verMinor = minor;
	}

	int32_t ver;
	int32_t verMajor;
	int32_t verMinor;
};

inline std::ostream& operator<< (std::ostream& os, const Version& v){
	return os << v.ver << "." << v.verMajor << "." << v.verMinor;
}

inline bool operator==(const Version& lhs, const Version& rhs){
	return lhs.ver == rhs.ver && lhs.verMajor == rhs.verMajor && lhs.verMinor == rhs.verMinor;
}

inline bool operator!=(const Version& lhs, const Version& rhs){
	return !(lhs==rhs);
}

inline bool operator< (const Version& lhs, const Version& rhs){
	if(lhs.verMinor < rhs.verMinor){
		return true;
	} else if(lhs.verMajor < rhs.verMajor){
		return true;
	} else if(lhs.ver < rhs.ver){
		return true;
	}

	return false;
}

inline bool operator> (const Version& lhs, const Version& rhs){
	return rhs < lhs;
}

inline bool operator<= (const Version& lhs, const Version& rhs){
	return !(lhs > rhs);
}

inline bool operator>= (const Version& lhs, const Version& rhs){
	return !(lhs < rhs);
}

const Version GameVer(1,0,0);

#endif //VERSION_H