/*
 * smartPtr.hpp
 *
 *  Created on: 25 mai 2011
 *      Author: ANTOINE Sylvestre
 */

#ifndef SMARTPTR_HPP_
#define SMARTPTR_HPP_

/*! \namespace ami
 * 	Espace de nommage regroupant les outils de Aumiis
 */
namespace ami
{

/*! \class  SmartPtr
 * 	\brief Classe representant un smartPtr.
 * 	La classe definit les operations classiques d'un smartPtr. Cela evite juste de reecrire le meme
 * 	code dans les smartPtr (shared_ptr, copy_ptr) implementes plus bas. Note : Cette classe est viturelle pure.
 */
template <typename Type>
class SmartPtr
{
protected:

	Type* m_pointer;

	SmartPtr () :
		m_pointer(0)
	{
	}

	SmartPtr (const SmartPtr<Type>& smart_ptr) :
		m_pointer(smart_ptr.m_pointer)
	{
	}

	SmartPtr (Type* ptr) :
		m_pointer(ptr)
	{
	}

	virtual ~SmartPtr ()
	{
	}

	virtual void release () = 0;

public:

	Type& operator* ()
	{
		return *m_pointer;
	}

	const Type& operator* () const
	{
		return *m_pointer;
	}

	Type* operator-> ()
	{
		return m_pointer;
	}

	const Type* operator-> () const
	{
		return m_pointer;
	}

	const Type * get () const
	{
		return m_pointer;
	}

	Type * get ()
	{
		return m_pointer;
	}

	bool operator== (const SmartPtr<Type>& SmartPtr) const
	{
		return m_pointer == SmartPtr.m_pointer;
	}

	bool operator!= (const SmartPtr<Type>& SmartPtr) const
	{
		return m_pointer != SmartPtr.m_pointer;
	}
};

/*! Simple macro afin d'eviter de reecrire cet operateur a chaque fois. */
#define CLONE_METHOD(Type)	public: virtual Type* clone () const { return new Type(*this); }

/*! \class  copy_ptr
 * 	\brief Classe representant des pointeurs de copie d'objets.
 * 	La classe gere un pointeur. Si l'on fait une affectation avec ce pointeur, l'objet au bout du pointeur sera copie et ce ne sera pas
 * 	seulement l'adresse du pointeur	qui le sera.
 * 	ATTENTION : Ne pas utiliser de type primitif avec ce smart_ptr!
 */
template <class Type>
class copy_ptr : public SmartPtr<Type>
{
	virtual void release ()
	{
		if (this ->m_pointer)
			delete this->m_pointer;
		this->m_pointer = NULL;
	}

public:

	copy_ptr () :
		SmartPtr<Type> ()
	{
	}

	copy_ptr (const copy_ptr<Type>& copy_ptr) :
		SmartPtr<Type> ()
	{
		if (copy_ptr.m_pointer)
			this->m_pointer = copy_ptr.m_pointer->clone();
	}

	copy_ptr (Type* ptr) :
		SmartPtr<Type> (ptr)
	{
	}

	virtual ~copy_ptr ()
	{
		release();
	}

	copy_ptr& operator= (const copy_ptr<Type>& copy_ptr)
	{
		release();
		if (copy_ptr.m_pointer)
			this->m_pointer = copy_ptr.m_pointer->clone();
		return *this;
	}

	copy_ptr& operator= (Type* pointer)
	{
		release();
		this->m_pointer = pointer;
		return *this;
	}
};

/*! \class  shared_ptr
 * 	\brief Classe representant des pointeurs partage.
 * 	La classe gere un pointeur. Celui ci est detruit si plus personne ne l'utilise.
 *  \deprecated {  Use std::shared_ptr ! }
 */
template <typename Type>
class shared_ptr : public SmartPtr<Type>
{
	virtual void release ()
	{
		if (m_counter != 0)
		{
			(*m_counter)--;
			if (*m_counter <= 0)
			{
				delete m_counter;
				if (this->m_pointer != 0)
					delete this->m_pointer;
			}
		}
	}

	int * m_counter;

public:

	shared_ptr () :
		SmartPtr<Type> (0), m_counter(0)
	{
	}

	shared_ptr (const shared_ptr<Type>& shared_ptr) :
		SmartPtr<Type> (shared_ptr.m_pointer), m_counter(shared_ptr.m_counter)
	{
		++m_counter;
	}

	shared_ptr (Type* ptr) :
		SmartPtr<Type> (ptr)
	{
		m_counter = new int(1);
	}

	virtual ~shared_ptr ()
	{
		release();
	}

	shared_ptr& operator= (const shared_ptr<Type>& smart_ptr)
	{
		release();
		this->m_pointer = smart_ptr.m_pointer;
		m_counter = smart_ptr.m_counter;
		++m_counter;
		return *this;
	}

	shared_ptr& operator= (Type* pointer)
	{
		release();
		this->m_pointer = pointer;
		m_counter = new int(1);
		return *this;
	}
};

} // namespace ami

#endif /* SMARTPTR_HPP_ */
