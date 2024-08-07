import pandas as pd

def combine_csv_files(file_paths, output_file):
    # Read all CSV files and concatenate them into a single DataFrame
    try:
        dfs = [pd.read_csv(file) for file in file_paths]
        combined_df = pd.concat(dfs, ignore_index=True)
        combined_df.to_csv(output_file, index=False)
        print(f"Combined CSV file saved as {output_file}")
    except FileNotFoundError as e:
        print(f"File not found: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    # List of CSV files to combine for uniform and Gaussian data
    uniform_files = [
        'dumbKnnUniform.csv',
        'bucketKnnUniform.csv',
        'quadTreeUniform.csv',
        'kdTreeUniform.csv'
    ]
    
    gaussian_files = [
        'dumbKnnGaussian.csv',
        'bucketKnnGaussian.csv',
        'quadTreeGaussian.csv',
        'kdTreeGaussian.csv'
    ]
    
    # Combine uniform and Gaussian files
    # all_files = uniform_files 
    all_files = gaussian_files
    output_file = 'combinedData_Gaussian.csv'
    combine_csv_files(all_files, output_file)
