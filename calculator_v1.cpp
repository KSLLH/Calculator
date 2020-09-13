#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Calculator{
public:
	static  Calculator& GetInstance(){
		static Calculator instance {};
		return instance;
	}
	
	void Start(){
		string exp = "";
		vector<string> suffix_exp;
	 	while(1){
	 		cout << "Input expression or 'quit' to stop:" << endl;
			getline(cin, exp);
			if(exp.size() > 0 && (exp[0] == '-' || exp[0] == '+') ) exp = "0" + exp;
			if(DEBUG_) cout << "Expression: " << exp << endl;
			if(exp == "quit"){
				return;
			}
			suffix_exp = GetSuffixExp(exp);
			if(DEBUG_){
				cout << "suffix expression: ";
				for(int j = 0; j < suffix_exp.size(); j++)
					cout << suffix_exp[j] << " ";
			}
			if(DEBUG_) cout << endl;
			cout << "Ans = " << Compute(suffix_exp) << endl;
		}
	}
	
private:
	Calculator(){};
	
	vector<string> GetSuffixExp(const string& exp){
		vector<string> suffix_exp;
		stack<char> op;
		for(int left = 0, right = 0; right <= exp.size(); right++){
			if(right == exp.size()){
				suffix_exp.push_back(exp.substr(left, right - left));
			}
			else if(exp[right] == '('){
				suffix_exp.push_back(exp.substr(left, right - left));
				op.push('(');
				left = right + 1;
			}
			else if(exp[right] == ')'){
				suffix_exp.push_back(exp.substr(left, right - left));
				if(op.empty()){
					cout << "Invalid expression, program abort" << endl;
					abort();
				}
				while(!op.empty() && op.top() != '(') {
					string op_str {op.top()};
					suffix_exp.push_back(op_str);
					op.pop();
				}
				if(!op.empty() && op.top() == '(') op.pop();
				else{
					cout << "Invalid expression, program abort" << endl;
					abort();
				}
				left = right + 1;
			}
			else if(exp[right] == '*' || exp[right] == '/'){
				suffix_exp.push_back(exp.substr(left, right - left));
				if(op.empty() || op.top() == '(' || op.top() == '+' || op.top() == '-'){
					op.push(exp[right]);
				}
				else if(op.top() == '*' || op.top() == '/'){
					string op_str {op.top()};
					suffix_exp.push_back(op_str);
					op.pop();
					op.push(exp[right]);
				}
				left = right + 1;
			}
			else if(exp[right] == '+' || exp[right] == '-'){
				suffix_exp.push_back(exp.substr(left, right - left));
				if(op.empty() || op.top() == '(') op.push(exp[right]);
				else{
					string op_str {op.top()};
					suffix_exp.push_back(op_str);
					op.pop();
					op.push(exp[right]);
				}
				left = right + 1;
			}			
		}
		while(!op.empty()){
			string op_str {op.top()};
			suffix_exp.push_back(op_str);
			op.pop();
		}
		return suffix_exp;
	}
	
	int Compute(const vector<string>& suffix_exp){
		int ans = 0;
		stack<int> nums;
		int a, b;
		int* pnumber = new int;
		for(int j = 0; j < suffix_exp.size(); j++){
			if(suffix_exp[j] == "+"){
				if(!nums.empty()) {
					b = nums.top();
					nums.pop();
				}
				else {
					cout << "Invalid expression, program abort." << endl;
					abort();
				}
				if(!nums.empty()) {
					a = nums.top();
					nums.pop();
				}
				else {
					cout << "Invalid expression, program abort." << endl;
					abort();
				}
				nums.push(a + b);
			}
			else if(suffix_exp[j] == "-"){
				if(!nums.empty()) {
					b = nums.top();
					nums.pop();
				}
				else {
					cout << "Invalid expression, program abort." << endl;
					abort();
				}
				if(!nums.empty()) {
					a = nums.top();
					nums.pop();
				}
				else {
					cout << "Invalid expression, program abort." << endl;
					abort();
				}
				nums.push(a - b);
			}
			else if(suffix_exp[j] == "*"){
				if(!nums.empty()) {
					b = nums.top();
					nums.pop();
				}
				else {
					cout << "Invalid expression, program abort." << endl;
					abort();
				}
				if(!nums.empty()) {
					a = nums.top();
					nums.pop();
				}
				else {
					cout << "Invalid expression, program abort." << endl;
					abort();
				}
				nums.push(a * b);
			}
			else if(suffix_exp[j] == "/"){
				if(!nums.empty()) {
					b = nums.top();
					nums.pop();
				}
				else {
					cout << "Invalid expression, program abort." << endl;
					abort();
				}
				if(!nums.empty()) {
					a = nums.top();
					nums.pop();
				}
				else {
					cout << "Invalid expression, program abort." << endl;
					abort();
				}
				nums.push(a / b);
			}
			else {
				string num_str = Trim(suffix_exp[j]);
				if(num_str.size() > 0) nums.push(stoi(num_str));
			}
		}
		ans = nums.top();
		nums.pop();
		if(nums.empty()) return ans;
		cout << "Invalid expression. program abort." << endl;
		abort();
	}
	
	string Trim(const string& str){
		int left = 0;
		int right = str.size();
		while(left <= right && str[left] == ' ') left++;
		while(right >= left && str[right] == ' ') right--;
		if(left <= right) return str.substr(left, right + 1 - left);
		else return "";
	}
	
	bool DEBUG_ = true;
};

int main(int argc, char* argv[]){
	Calculator::GetInstance().Start();
	return 0;
}
