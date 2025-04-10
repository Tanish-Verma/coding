import numpy as np

def main():
    # Define the matrix
    matrix = np.array([
        [1, 2, 4, 1],
        [2, -5, 3, -5],
        [1, -4, 4, 7],
        [2, -3, 2, -5]
    ])

    # Calculate the condition number
    condition_number = np.linalg.cond(matrix, p=np.inf)

    # Print the condition number
    print(f"Condition number of the matrix: {condition_number}")

if __name__ == "__main__":
    main()
