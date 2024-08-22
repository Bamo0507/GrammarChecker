import language_tool_python

tool = language_tool_python.LanguageTool('en-US')

def correct_sentence(sentence):
    for _ in range(3):
        matches = tool.check(sentence)
        corrections = []
        
        for match in matches:
            if match.replacements:
                corrections.append((match.offset, match.errorLength, match.replacements[0]))
        
        for offset, errorLength, replacement in sorted(corrections, reverse=True):
            sentence = sentence[:offset] + replacement + sentence[offset + errorLength:]
    
    return sentence

if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1:
        sentence = sys.argv[1]
        print(correct_sentence(sentence))
    else:
        print("No se proporcionó ninguna oración para corregir.")
