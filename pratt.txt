(-1 + 2) * 3 - -4

Precedence table (lowest to highest)

enum {
  PREC_NONE,
  PREC_ASSIGNMENT, // =
  PREC_OR,         // or
  PREC_AND,        // and
  PREC_EQUALITY,   // == !=
  PREC_COMPARISON, // < > <= >=
  PREC_TERM,       // + -
  PREC_FACTOR,     // * /
  PREC_UNARY,      // ! -
  PREC_CALL,       // . ()
  PREC_PPRIMARY
} Precedence;


compile():
    advance():
        parser.previous.type = '('
        parser.current.type = scanToken() = '('
    expression():
        parsePrecedence(PREC_ASSIGNMENT):
            advance():
                parser.previous.type = '('
                parser.current.type = scanToken() = '-'
            prefixRule = getRule(parser.previous.type)->prefix = grouping
            grouping():
                expression():
                    parsePrecedence(PREC_ASSIGNMENT):
                        advance():
                            parser.previous.type = '-'
                            parser.current.type = scanToken() = 'number' # '1'
                        prefixRule = getRule(parser.previous.type)->prefix = unary
                        unary():
                            parsePrecedence(PREC_UNARY):
                                advance():
                                    parser.previous.type = 'number' # '1'
                                    parser.current.type = scanToken() = '+'
                                prefixRule = getRule(parser.previous.type)->prefix = number
                                number():
                                    value = parser.previous.start # 1
                                    emitConstant(value)
                                while (precedence = PREC_UNARY <= getRule(parser.current.type)->precedence = PREC_TERM): # false
                            switch(operatorType): # '-'
                                case(TOKEN_MINUS):
                                    emitByte(OP_NEGATE) # '-1'
                        while (precedence = PREC_ASSIGNMENT <= getRule(parser.current.type)->precedence = PREC_TERM): # true
                            advance():
                                parser.previous.type = '+'
                                parser.current.type = scanToken() = 'number' # '2'
                            infixRule = getRule(parser.previous.type)->infix = binary
                            binary():
                                operatorType = parser.previous.type = '+'
                                rule = getRule(operatorType)
                                parsePrecedence(rule->precedence + 1): # PREC_FACTOR
                                    advance():
                                        parser.previous.type = 'number' # '2
                                        parser.current.type = scanToken() = ')'
                                    prefixRule = getRule(parser.previous.type)->prefix = number
                                    number():
                                        value = parser.previous.start # 2
                                        emitConstant(value)
                                    while (precedence = PREC_FACTOR <= getRule(parser.current.type)->precedence = PREC_NONE): # false
                                switch(operatorType): # '+'
                                    case(TOKEN_PLUS):
                                        emitByte(OP_ADD) # '(-1 + 2)'
                        while (precedence = PREC_ASSIGNMENT <= getRule(parser.current.type)->precedence = PREC_NONE): # false
                consume(TOKEN_RIGHT_PAREN):
                    advance():
                        parser.previous.type = ')'
                        parser.current.type = scanToken() = '*'
            while (precedence = PREC_ASSIGNMENT <= getRule(parser.current.type)->precedence = PREC_FACTOR): # true
                advance():
                    parser.previous.type = '*'
                    parser.current.type = scanToken() = 'number' # '3'
                infixRule = getRule(parser.previous.type)->infix = binary
                binary():
                    operatorType = parser.previous.type = '*'
                    rule = getRule(operatorType)
                    parsePrecedence(rule->precedence + 1): # PREC_UNARY
                        advance():
                            parser.previous.type = 'number' # '3'
                            parser.current.type = scanToken() =  '-'
                        prefixRule = getRule(parser.previous.type)->prefix = number
                        number():
                            value = parser.previous.start # 3
                            emitConstant(value)
                        while (precedence = PREC_UNARY <= getRule(parser.current.type)->precedence = PREC_TERM): # false
                    switch(operatorType): # '*'
                        case(TOKEN_PLUS):
                            emitByte(OP_ADD) # '(-1 + 2) * 3'
            while (precedence = PREC_ASSIGNMENT <= getRule(parser.current.type)->precedence = PREC_TERM): # true
                advance():
                    parser.previous.type = '-'
                    parser.current.type = scanToken() =  '-'
                    infixRule = getRule(parser.previous.type)->infix = binary
                    binary():
                        operatorType = parser.previous.type = '-'
                        rule = getRule(operatorType
                        parsePrecedence(rule->precedence + 1): # PREC_FACTOR
                            advance():
                                parser.previous.type = '-'
                                parser.current.type = scanToken() =  'number' # 4
                            prefixRule = getRule(parser.previous.type)->prefix = unary
                            unary():
                                parsePrecedence(PREC_UNARY):
                                    advance():
                                        parser.previous.type = 'number' # '4'
                                        parser.current.type = scanToken() = 'EOF'
                                    prefixRule = getRule(parser.previous.type)->prefix = number
                                    number():
                                        value = parser.previous.start # 4
                                        emitConstant(value)
                                    while (precedence = PREC_UNARY <= getRule(parser.current.type)->precedence = PREC_NONE): # false
                                switch(operatorType): # '-'
                                    case(TOKEN_MINUS):
                                        emitByte(OP_NEGATE) # '-4'
                            while (precedence = PREC_FACTOR <= getRule(parser.current.type)->precedence = PREC_NONE): # false
                        switch(operatorType): # '-'
                            case(TOKEN_MINUS):
                                emitByte(OP_SUBTRACT) # '(-1 + 2) * 3 - -4'
            while (precedence = PREC_ASSIGNMENT <= getRule(parser.current.type)->precedence = PREC_NONE): # false
    consume(TOKEN_EOF)
