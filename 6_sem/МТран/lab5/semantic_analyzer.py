import syntactic_analyzer


def main():
    statement = syntactic_analyzer.main()

    statement.semantic_analyze()

    return statement


if __name__ == '__main__':
    main()
