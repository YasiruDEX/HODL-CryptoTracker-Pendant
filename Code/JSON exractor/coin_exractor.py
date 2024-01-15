import json

# Load JSON data from the file
with open('data.json', 'r') as file:
    data = json.load(file)

# Initialize an empty list to store the items
coin_list = []

# Extract the items from the 'data' dictionary
for item in data['data']:
    instId = item['instId']
    coin = instId.split('-')[0]  # Extracting the coin symbol from instId
    coin_list.append(coin)

# Print the final list
print(coin_list)
