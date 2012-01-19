#pragma once

#define GETTER(klass, type, ev, iv)\
	type klass::get ## ev () const {\
		return iv;\
	}

#define SETTER(klass, type, ev, iv)\
	void klass::set ## ev (const type& v) {\
		iv = v;\
	}

#define GETSET(klass, type, ev, iv)\
	GETTER(klass, type, ev, iv)\
	SETTER(klass, type, ev, iv)

#define GETTER_P GETTER

#define SETTER_P(klass, type, ev, iv)\
	void klass::set ## ev (type v) {\
		iv = v;\
	}

#define GETSET_P(klass, type, ev, iv)\
	GETTER_P(klass, type, ev, iv)\
	SETTER_P(klass, type, ev, iv)
