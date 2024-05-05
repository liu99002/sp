import operator as op  # 導入 operator 模組，將其別名設為 op

# 定義一些基本的運算符，每個運算符都對應到 operator 模組中的一個函數
ENV = {'+': op.add, '-': op.sub, '*': op.mul, '/': op.truediv}

# Scheme 解釋器函數
def evaluate(exp, env={}):
    if isinstance(exp, list):  # 如果 exp 是列表，則該表達式為函數調用
        op = evaluate(exp[0], env)  # 遞歸地解釋運算符部分
        args = [evaluate(arg, env) for arg in exp[1:]]  # 遞歸地解釋參數部分
        return op(*args)  # 使用運算符函數對參數進行計算
    elif isinstance(exp, str) and (exp in env):  # 如果 exp 是字符串且存在於環境中，則該表達式為變數引用
        return env[exp]  # 返回變數對應的值
    else:  # 如果以上條件都不滿足，則 exp 為常數
        return exp  # 直接返回該常數值

# 測試 Scheme 解釋器
if __name__ == "__main__":
    # 定義一個簡單的 Scheme 表達式，計算表達式 (+ 2 (* 3 4)) 的值
    code = ['+', 2, ['*', 3, 4]]
    # 解釋和計算結果
    result = evaluate(code, ENV)
    print(code, '=', result)  # 輸出表達式和計算結果
