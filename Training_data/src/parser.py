def main():
    filename = 'data.txt'
    table_filename = 'tables.txt'
    scores_filename = 'scores.txt'
    tables = []
    scores = []

    count = 0;
    isTable = False
    isScore = False
    tableIndex = 0
    scoreIndex = 0
    with open(filename, 'r') as file:
        for line in file:
            if line[0].isnumeric():
                if isTable:
                    tables[tableIndex].append(line)
                else:
                    scoreIndex = scoreIndex +1 if isScore else scoreIndex
                    isTable = True
                    isScore = False
                    tables.append([line])
            else:
                if isScore:
                    scores[scoreIndex].append(line)
                else:
                    tableIndex = tableIndex+1 if isTable else tableIndex
                    isTable = False
                    isScore = True
                    scores.append([line])
    divider = "-"*10
    divider += "\n"
    with open('tables.txt', 'w') as table_file:
        for i in tables:
            for x in i:
                table_file.write(x)
            table_file.write(divider)
            
        
    with open('scores.txt', 'w') as scores_file:
        for i in scores:
            for x in i:
                scores_file.write(x)
            scores_file.write(divider)
 

if __name__ == '__main__':
    main()
