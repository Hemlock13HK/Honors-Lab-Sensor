import re
import pandas as pd

def extract_numbers(s_data):
    # Define a regular expression pattern to match numbers
    pattern = r'\d+\.\d+|\d+'
    # Use re.findall to extract all numbers from the statement
    numbers = re.findall(pattern, s_data)
    if len(numbers) >= 2:
        time, temperature = map(float, numbers[:2])
        time = time / 3600
        return time, temperature
    else:
        return None

def process_file(file_path):
    data_list = []
    with open(file_path, "r") as file:
        for line in file:
            result = extract_numbers(line)
            if result is not None:
                time, temperature = result
                data_list.append({'Time': time, 'Temperature': temperature})

    return data_list

def save_to_excel(data_list, excel_path):
    try:    
        data_frame = pd.DataFrame(data_list)
        data_frame.to_excel(excel_path, index=False)
        print(f"Data successfully saved to {excel_path}")

    except Exception as e:
        print(f"Error: {e}")

file_path = 'jsonfiles/TEST.TXT'
excel_path = 'sensordata2.xlsx'
sensor_data = process_file(file_path)
save_to_excel(sensor_data, excel_path)




