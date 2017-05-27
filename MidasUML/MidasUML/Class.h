#pragma once

#include "Var.h"
#include "Function.h"

#define N_MARGIN_X		8
#define N_MARGIN_Y		4
#define N_FONT_SIZE		70
#define N_FONT_WIDTH	5
#define N_FONT_HEIGHT	9
#define N_LINE_PADDING	2
#define N_HEIGHT		(N_FONT_HEIGHT + N_LINE_PADDING)

#define STR_CLASS_NAME	"Class Name"
#define STR_CLASS_ATTR	"Attributes"
#define STR_CLASS_FUNC	"Operation"

class Class
{
private:
	int m_key;
	CString m_name;
	POINT m_point;
	std::vector<Var> m_var;
	std::vector<Function> m_function;

public:
	Class(CString name, POINT point, std::vector<Var> var, std::vector<Function> function, int key);
	~Class();
	int getKey() { return m_key; }
	int getVarSize() { return m_var.size(); }
	int getFunctionSize() { return m_function.size(); }
	CString getName() { return m_name; }
	POINT getPoint() { return m_point; }
	std::vector<Var> getVarInfo() { return m_var; }
	std::vector<Function> getFunctionInfo() { return m_function; }
	void addVar(Var var) { m_var.push_back(var); }
	void addFunction(Function function) { m_function.push_back(function); }
	void editVar(int id, ACCESS_TYPE at, CString name, CString type) { m_var[id].edit(at, name, type); }
	void editName(CString name) { m_name = name; }
	void editFunction(int id, ACCESS_TYPE at, CString return_type, CString name, CString parameter) {
		m_function[id].edit(at, return_type, name, parameter);
	}
	void deleteVar(int id) { m_var.erase(m_var.begin() + id); }
	void deleteFunction(int id) { m_function.erase(m_function.begin() + id); }

	int getHorizonSize();
	int getVerticalSize();

	POINT getUpCenter();
	POINT getDownCenter();
	POINT getRightCenter();
	POINT getLeftCenter();

	void drawClass(CDC * pDC);
};

