#ifndef __IDGMBH_SMARTPTR__
#define __IDGMBH_SMARTPTR__

/**
 * URL: /trunk/include/SmartPtr.h
 * Repository UUID: 6ed4c990-5aa0-6b45-94ab-72ba944e19f8
 * Revision: 78
 * Last Changed Author: twieczorek
 * Last Changed Rev: 70
 * Last Changed Date: 2004-11-05 10:15:23 +0100 (Fr, 05 Nov 2004)
 * Text Last Updated: 2004-12-23 17:54:06 +0100 (Do, 23 Dez 2004)
 * Properties Last Updated: 2004-12-23 17:54:05 +0100 (Do, 23 Dez 2004)
 */

#if _MSC_VER > 1000
#pragma once
#endif

#pragma warning(disable:4284)  // Warning für Nicht-Klassen-Template-Params bei "->"

/**
 * Implementiert einen Smart Pointer. Nach der Vorgabe aus:<br />
 * <br />
 * <address>Modern C++ Design: Generic Programming and Design Patterns Applied<br />
 * (Addison-Wesley, 2001, ISBN 0-201-70431-5)<br />
 * Chapter 7</address>
 *
 * <dl>
 *    <dt>0.9.0.4</dt>
 *       <dd>BugFix: operator =(TSmartPtr&)</dd>
 *       <dd>Angepasst: TSmartPtr(TSmartPtr&)</dd>
 *    <dt>0.9.0.3</dt>
 *       <dd>BugFix: {@link GetImplRef(TSmartPtr<T>&)}</dd>
 *       <dd>Hinzugefügt: {@link DeepCopy(TSmartPtr<T>&,constT&)}</dd>
 *    <dt>0.9.0.2</dt>
 *       <dd>BugFix: {@link Release(TSsmartPtr<T>&,T*&)}</dd>
 *    <dt>0.9.0.1</dt>
 *       <dd>Hinzugefügt: {@link TSmartPtr<T>(T&)}</dd>
 *       <dd>Hinzugefügt: {@link Reset(TSmartPtr<T>&)}</dd>
 *       <dd>BugFix: {@link operator=(TSmartPtr<T>&)}</dd>
 * </dl>
 *
 * @author TW
 * @version 0.9.0.4
 */
template <class T>
class TSmartPtr
{
	friend T* GetImpl(TSmartPtr& sp);
	friend const T* GetImpl(const TSmartPtr& sp);
	friend T*& GetImplRef(TSmartPtr& sp);
	friend TSmartPtr& Reset(TSmartPtr& sp, T* source);
	friend void Reset(TSmartPtr& sp);
	friend void Release(TSmartPtr& sp, T*& destination);
	friend const T& DeepCopy(TSmartPtr<T>& sp, const T& value);

private:
	/**
	 * Private Klasse für den Operator {@link TSmartPtr#CTester*()}.
	 *
	 * @author TW
	 * @since 0.9.0.0
	 */
	class CTester
	{
	private:
		/**
		 * Sperrt den Zugriff auf den delete-Operator.
		 *
		 * @since 0.9.0.0
		 */
		void operator delete(void*);
	};

public:
	/**
	 * Konstruktor. Akzeptiert einen Pointer auf ein Objekt des Typs <code>T</code>.
	 * Beispiel:<br />
	 * <br />
	 * <code>TSmartPtr&lt;CFile&gt; spoTemp(new CFile(_T("C:\\TEMP.DAT"), CFile::modeRead));</code>
	 *
	 * @param pObj Der Pointer, den der SmartPointer kapseln soll.
	 * @since 0.9.0.0
	 */
	inline explicit TSmartPtr(T* pObj) : m_pObj(pObj) {}

	/**
	 * Kopierkonstruktor. Implementiert eine zerstörende Kopie des rechten Objektes. D.h. der
	 * interne Pointer des zu kopierenden Objektes wird dem neu erzeugten zugeordnet, und
	 * anschließend auf <code>NULL</code> gesetzt. Beispiel:<br />
	 * <br />
	 * <code>
	 * TSmartPtr&lt;CFile&gt; spZuKopieren(new CFile());       // leeres CFile-Objekt<br />
	 * TSmartPtr&lt;CFile&gt; spZuErzeugen(spLinks);           // Kopie erstellen<br />
	 * <br />
	 * // Jetzt zeigt spZuErzeugen auf das CFile-Objekt, das für spZuKopieren erzeugt wurde,<br />
	 * // und spZuKopieren zeigt auf NULL.stört.<br />
	 * </code>
	 *
	 * <dl>
	 *    <dt>0.9.0.4</dt>
	 *       <dd>Implementiert nicht mehr implizit operator =(TSmartPtr&).</dd>
	 * </dl>
	 *
	 * @param other Eine Referenz auf einen anderen SmartPointer des selben Typs.
	 * @return Eine Referenz auf den linken SmartPointer.
	 * @see operator=(TSmartPtr<T>&)
	 * @since 0.9.0.1
	 * @version 0.9.0.4
	 */
	inline TSmartPtr(TSmartPtr& other)
	{
		m_pObj       = other.m_pObj;
		other.m_pObj = NULL;
	}

	/**
	 * Zuweisungsoperator. Implementiert eine zerstörende Kopie des rechten Objektes. D.h. der
	 * interne Pointer des rechten Objekteswird dem linken zugeordnet, und anschließend auf
	 * <code>NULL</code> gesetzt. Beispiel:<br />
	 * <br />
	 * <code>
	 * TSmartPtr&lt;CFile&gt; spLinks(new CFile());       // leeres CFile-Objekt<br />
	 * TSmartPtr&lt;CFile&gt; spRechts(new CStdioFile()); // leeres CStdioFile-Objekt<br />
	 * <br />
	 * spLinks = spRechts;  // zerstörende Kopie von spRechts nach spLinks.<br />
	 * <br />
	 * // Jetzt zeigt spLinks auf das CStdioFile-Objekt, das für spRechts erzeugt wurde,<br />
	 * // und spRechts zeigt auf NULL. Während der Kopie wurde das für spLinks erzeugte<br />
	 * // CFile-Objekt implizit zerstört.<br />
	 * </code>
	 *
	 * <dl>
	 *    <dt>0.9.0.4</dt>
	 *       <dd>Das bei der Zuweisung verloren gehende Objekt wurde nicht zerstört.</dd>
	 *    <dt>0.9.0.1</dt>
	 *       <dd>Das <code>return</code>-Statement fehlte.</dd>
	 * </dl>
	 *
	 * @param other Eine Referenz auf einen anderen SmartPointer des selben Typs.
	 * @return Eine Referenz auf den linken SmartPointer.
	 * @see TSmartPtr<T>(TSmartPtr<T>&)
	 * @since 0.9.0.0
	 * @version 0.9.0.4
	 */
	inline TSmartPtr& operator=(TSmartPtr& other)
	{
		if (m_pObj)
		{
			delete m_pObj;
		}

		m_pObj       = other.m_pObj;
		other.m_pObj = NULL;
		return *this;
	}

	/**
	 * Destruktor. Implementiert die automatische Zerstörung des internen Objektes.
	 *
	 * @since 0.9.0.0
	 */
	inline ~TSmartPtr()
	{
		if (m_pObj)
		{
			delete m_pObj;
			m_pObj = NULL;
		}
	}

	/**
	 * Dereferenzierungsoperator. Implementiert das pointerartige Verhalten der Klasse.
	 *
	 * @return eine Referenz des internen Objektes
	 * @since 0.9.0.0
	 */
	inline T& operator*() const
	{
		return *m_pObj;
	}

	inline TSmartPtr& operator &()
	{
		return *this;
	}

	/**
	 * Dereferenzierungsoperator. Implementiert das pointerartige Verhalten der Klasse.
	 * Hierdurch können wie gewohnt die Member-Funktionen des internen Objek-
	 * tes angesprochen werden.
	 *
	 * @since 0.9.0.0
	 */
	inline T* operator->() const
	{
		return m_pObj;
	}

	/**
	 * Implementiert die Möglichkeit <code>if (!sp) ...</code> zu schreiben.
	 * Semantisch äquivalent zu <code>sp.m_pObj == NULL</code>
	 *
	 * @return <code>true</code>, falls der SmartPointer auf den NULL-Pointer zeigt, ansonsten <code>false</code>.
	 * @sicne 0.9.0.0
	 */
	inline bool operator !() const
	{
		return m_pObj == NULL;
	}

	/**
	 * Implementiert die Möglichkeit <code>if (sp) ...</code> zu schreiben.
	 * Semantisch äquivalent zu <code>sp.m_pObj != NULL</code>
	 *
	 * @return <code>NULL</code>, falls der SmartPointer auf den NULL-Pointer zeigt, ansonsten eine nicht weiter zu verwendende Speicheradresse.
	 * @since 0.9.0.0
	 */
	inline operator CTester*() const
	{
		if (!m_pObj)
		{
			return NULL;
		}
		static CTester oTester;
		return &oTester;
	}

	/**
	 * Vergleichsoperator. Vergleicht einen Pointer des Typs <code>T</code> mit dem internen
	 * Pointer und zeigt an, ob sie auf den gleichen Speicherbereich zeigen oder nicht.
	 *
	 * @param rhs ein Pointer auf ein Objekt des Typs <code>T</code>.
	 * @return <code>true</code>, falls die beiden Pointer auf den selben Speicherbereich zeigen, ansonsten <code>false</code>.
	 * @since 0.9.0.0
	 */
	inline bool operator ==(const T* rhs) const
	{
		return m_pObj == rhs;
	}

	/**
	 * Vergleichsoperator. Vergleicht einen Pointer des Typs <code>T</code> mit dem internen
	 * Pointer und zeigt an, ob sie auf den gleichen Speicherbereich zeigen oder nicht.
	 *
	 * @param lhs ein Pointer auf ein Objekt des Typs <code>T</code>.
	 * @param rhs eine Referenz auf ein Objekt dieser Klasse.
	 * @return <code>true</code>, falls die beiden Pointer auf den selben Speicherbereich zeigen, ansonsten <code>false</code>.
	 * @since 0.9.0.0
	 */
	static inline bool operator ==(const T* lhs, const TSmartPtr& rhs)
	{
		return lhs == rhs.m_pObj;
	}

	/**
	 * Vergleichsoperator. Vergleicht einen Pointer eines beliebigen Typs mit dem internen Pointer
	 * und zeigt an, ob sie auf den gleichen Speicherbereich zeigen oder nicht.
	 *
	 * @param rhs ein Pointer auf ein Objekt eines beliebigen Typs.
	 * @return <code>true</code>, falls die beiden Pointer auf den selben Speicherbereich zeigen, ansonsten <code>false</code>.
	 * @since 0.9.0.0
	 */
	template <class U> inline bool operator ==(const U* rhs) const
	{
		return m_pObj == rhs;
	}

	/**
	 * Vergleichsoperator. Vergleicht einen Pointer eines beliebigen Typs mit dem internen Pointer
	 * und zeigt an, ob sie auf den gleichen Speicherbereich zeigen oder nicht.
	 *
	 * @param lhs ein Pointer auf ein Objekt eines beliebigen Typs.
	 * @param rhs eine Referenz auf ein Objekt dieser Klasse.
	 * @return <code>true</code>, falls die beiden Pointer auf den selben Speicherbereich zeigen, ansonsten <code>false</code>.
	 * @since 0.9.0.0
	 */
	template <class U> static inline bool operator ==(const U* lhs, const TSmartPtr& rhs)
	{
		return lhs == rhs.m_pObj;
	}

	/**
	 * Vergleichsoperator. Vergleicht zwei SmartPointer unterschiedlichen Typs und zeigt an, ob sie
	 * auf den selben Speicherbereich zeigen oder nicht.
	 *
	 * @param rhs eine Referenz auf einen SmartPointer eines anderen Typs.
	 * @return <code>true</code>, falls die beiden Objekte auf den selben Speicherbereich zeigen, ansonsten <code>false</code>.
	 * @since 0.9.0.0
	 */
	template <class U> inline bool operator ==(const TSmartPtr<U>& rhs) const
	{
		return m_pObj == rhs.m_pObj;
	}

	/**
	 * Ungleichoperator. Gegenstück zu {@link #operator==(constT*)}
	 *
	 * @param rhs ein Pointer auf ein Objekt des Typs <code>T</code>.
	 * @return <code>true</code>, falls die beiden Pointer nicht auf den selben Speicherbereich zeigen, ansonsten <code>false</code>.
	 * @since 0.9.0.0
	 */
	inline bool operator !=(const T* rhs) const
	{
		return m_pObj != rhs;
	}

	/**
	 * Ungleichoperator. Gegenstück zu {@link #operator==(constT*,constTSmartPtr&)}
	 *
	 * @param lhs ein Pointer auf ein Objekt des Typs <code>T</code>.
	 * @param rhs eine Referenz auf ein Objekt dieser Klasse.
	 * @return <code>true</code>, falls die beiden Pointer nicht auf den selben Speicherbereich zeigen, ansonsten <code>false</code>.
	 * @since 0.9.0.0
	 */
	static inline bool operator !=(const T* lhs, const TSmartPtr& rhs)
	{
		return lhs != rhs.m_pObj;
	}

	/**
	 * Ungleichoperator. Gegenstück zu {@link #operator==(constU*)}
	 *
	 * @param rhs ein Pointer auf ein Objekt eines beliebigen Typs.
	 * @return <code>true</code>, falls die beiden Pointer nicht auf den selben Speicherbereich zeigen, ansonsten <code>false</code>.
	 * @since 0.9.0.0
	 */
	template <class U> inline bool operator !=(const U* rhs) const
	{
		return m_pObj != rhs;
	}

	/**
	 * Ungleichoperator. Gegenstück zu {@link #operator==(constU*,constTSmartPtr&)}
	 *
	 * @param lhs ein Pointer auf ein Objekt eines beliebigen Typs.
	 * @param rhs eine Referenz auf ein Objekt dieser Klasse.
	 * @return <code>true</code>, falls die beiden Pointer nicht auf den selben Speicherbereich zeigen, ansonsten <code>false</code>.
	 * @since 0.9.0.0
	 */
	template <class U> static inline bool operator !=(const U* lhs, const TSmartPtr& rhs)
	{
		return lhs != rhs.m_pObj;
	}

	/**
	 * Ungleichoperator. Gegenstück zu {@link #operator==(constTSmartPtr&lt;U&gt;&)}
	 *
	 * @param lhs ein Pointer auf ein Objekt eines beliebigen Typs.
	 * @param rhs eine Referenz auf einen SmartPointer eines beliebigen Typs.
	 * @return <code>true</code>, falls die beiden Pointer nicht auf den selben Speicherbereich zeigen, ansonsten <code>false</code>.
	 * @since 0.9.0.0
	 */
	template <class U> inline bool operator !=(const TSmartPtr<U>& rhs) const
	{
		return m_pObj != rhs.m_pObj;
	}

private:
	T* m_pObj;

	/**
	 * Ordnungsoperatoren werden nicht unterstützt!
	 *
	 * @since 0.9.0.0
	 */
	template <class U> inline bool operator <(const U&); // Undefiniert!

	/**
	 * Ordnungsoperatoren werden nicht unterstützt!
	 *
	 * @since 0.9.0.0
	 */
	template <class U> static inline bool operator <(const T&, const TSmartPtr<U>&); // Undefiniert!
};

/**
 * Zugriffsfunktion auf SmartPointer. Gibt den internen Pointer auf das verwaltete Objekt zurück.
 *
 * @param sp Der SmartPointer, dessen gekapselten Pointer man erhalten will.
 * @return Die Speicheradresse des intern verwalteten Objektes.
 */
template <class T> inline T* GetImpl(TSmartPtr<T>& sp)
{
	return sp.m_pObj;
}

/**
 * Zugriffsfunktion auf SmartPointer. Gibt den internen Pointer auf das verwaltete Objekt zurück.
 *
 * @param sp Der SmartPointer, dessen gekapselten Pointer man erhalten will.
 * @return Die Speicheradresse des intern verwalteten Objektes.
 */
template <class T> inline const T* GetImpl(const TSmartPtr<T>& sp)
{
	return sp.m_pObj;
}

/**
 * Zugriffsfunktion auf SmartPointer. Gibt eine Referenz auf den internen Objekt-Pointer zurück.
 * Mit Vorsicht zu genießen, da diese Referenz nicht <code>const</code> ist.
 *
 * <dl>
 *    <dt>0.9.0.3</dt>
 *    <dd>Es wurde beim Rückgabewert erneut die Referenz von <code>m_pObj</code> genommen.</dd>
 * </dl>
 *
 * @param sp Der SmartPointer, dessen gekapselten Pointer man erhalten will.
 * @return Eine Referenz auf den internen Objektpointer.
 * @since 0.9.0.0
 * @version 0.9.0.3
 */
template <class T> inline T*& GetImplRef(TSmartPtr<T>& sp)
{
	return sp.m_pObj;
}

/**
 * Zugriffsfunktion auf SmartPointer. Tauscht den internen Objekt-Pointer gegen den übergebenen
 * aus. Dabei wird implizit das Objekt zerstört.
 *
 * @param sp Der SmartPointer, dessen internen Pointer man ändern möchte.
 * @param source Der Pointer, der dem SmartPointer zugewiesen werden soll.
 * @return eine Referenz auf den geänderten SmartPointer <code>sp</code>.
 * @since 0.9.0.0
 */
template <class T> inline TSmartPtr<T>& Reset(TSmartPtr<T>& sp, T* source)
{
	if (sp.m_pObj)
	{
		delete sp.m_pObj;
	}
	sp.m_pObj = source;
	return sp;
}

/**
 * Zerstört das im übergebenen SmartPointer enthaltene Objekt.
 *
 * @param sp Der SmartPointer, dessen internen Pointer man zerstören möchte.
 * @since 0.9.0.1
 */
template <class T> inline void Reset(TSmartPtr<T>& sp)
{
	if (sp.m_pObj)
	{
		delete sp.m_pObj;
		sp.m_pObj = NULL;
	}
}

/**
 * Zugriffsfunktion auf SmartPointer.Kopiert den internen Objekt-Pointer in den übergebenen
 * Pointer und setzt ihn dann auf <code>NUL</code>. Dabei wird das Objekt nicht zerstört, ist
 * auch nicht mehr diesem SmartPointer zugeordnet, und muss demnach manuell zerstört werden.
 *
 * <dl>
 *    <dt>0.9.0.2</dt>
 *    <dd>Das <code>es wurde bei der Zuweisung erneut die Referenz von <code>destination</code> genommen.</dd>
 * </dl>
 *
 * @param sp Der SmartPointer, dessen Objekt-Pointer man übernehmen möchte.
 * @param destination Der Pointer, der den Speicherbereich des internen Objektes erhalten soll.
 * @version 0.9.0.2
 * @since 0.9.0.0
 */
template <class T> inline void Release(TSmartPtr<T>& sp, T*& destination)
{
	destination = sp.m_pObj;
	sp.m_pObj = NULL;
}

/**
 * Führt eine DeepCopy vom übergebenen Parameter mittels des Kopierkonstruktors in den SmartPointer durch.
 * Der Kopierkonstruktor muss für diesen Paramerter definiert sein.
 *
 * @param sp Der SmartPointer, dessen Objekt-Pointer man übernehmen möchte.
 * @param destination Der Pointer, der den Speicherbereich des internen Objektes erhalten soll.
 * @since 0.9.0.3
 */
template <class T> inline const T& DeepCopy(TSmartPtr<T>& sp, const T& value)
{
	if (sp.m_pObj == NULL)
	{
		sp.m_pObj = new T(value);
	}
	else
	{
		*sp.m_pObj = value;
	}

	return *sp.m_pObj;
}

#pragma warning(default:4284)

#endif