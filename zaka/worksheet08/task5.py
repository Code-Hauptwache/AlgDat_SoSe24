def evaluate_rpn(expression):
    stack = []
    operators = set(['+', '-', '*', '/'])

    for token in expression.split():
        if token not in operators:
            # Token is a number, push it to the stack
            stack.append(float(token))
        else:
            # Token is an operator, pop the top two elements from the stack
            b = stack.pop()
            a = stack.pop()

            if token == '+':
                result = a + b
            elif token == '-':
                result = a - b
            elif token == '*':
                result = a * b
            elif token == '/':
                result = a / b

            # Push the result back to the stack
            stack.append(result)

    # The final result is the only element left in the stack
    return stack.pop()

# Beispielhafte Benutzung
expression = "a b c d / e f / + - *"
values = {
    'a': 5,
    'b': 2,
    'c': 10,
    'd': 4,
    'e': 8,
    'f': 2
}
# Variablen durch ihre Werte ersetzen
for key, value in values.items():
    expression = expression.replace(key, str(value))

print(f"Expression: {expression}")
result = evaluate_rpn(expression)
print(f"Result: {result}")