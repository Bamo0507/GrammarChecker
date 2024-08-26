import language_tool_python

# Inicializa la herramienta de corrección gramatical para inglés estadounidense
tool = language_tool_python.LanguageTool('en-US')

def correct_sentence(sentence):
    """
    Corrige la gramática de una oración dada utilizando LanguageTool.
    
    Parámetros:
    - sentence (str): La oración que necesita ser corregida.
    
    Retorna:
    - str: La oración corregida.
    """
    for _ in range(3):  # Realiza hasta tres iteraciones para mejorar la corrección
        matches = tool.check(sentence)  # Verifica la gramática de la oración
        corrections = []

        # Recolecta las correcciones necesarias
        for match in matches:
            if match.replacements:
                corrections.append((match.offset, match.errorLength, match.replacements[0]))
        
        # Aplica las correcciones de manera inversa para evitar conflictos de offset
        for offset, errorLength, replacement in sorted(corrections, reverse=True):
            sentence = sentence[:offset] + replacement + sentence[offset + errorLength:]
    
    return sentence

if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1:
        sentence = sys.argv[1]
        print(correct_sentence(sentence))  # Imprime la oración corregida
    else:
        print("No se proporcionó ninguna oración para corregir.")
