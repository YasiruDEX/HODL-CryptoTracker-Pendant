coin_list = ['CETUS', 'SUSHI', 'XLM', 'CRO', 'UNI', 'WAVES', 'APE', 'USTC', 'INJ', 'APT', 'NEO', 'SNX', 'AVAX', 'SAND', 'LPT', 'RNDR', 'FLOKI', 'MEME', 'DOGE', 'VRA', 'PERP', 'STX', 'YFI', 'MKR', 'UNI', 'ACE', 'AVAX', 'AUCTION', 'FIL', 'ETH', 'SHIB', 'FLM', 'GMX', 'ARB', 'MINA', 'LUNC', 'IMX', 'SUI', 'XTZ', 'EOS', 'CVC', 'PEPE', 'CRV', 'LRC', 'DYDX', 'KISHU', 'SLP', 'CHZ', 'BCH', 'GODS', 'BLUR', 'YGG', 'JOE', 'AAVE', 'METIS', 'EGLD', 'AGLD', 'ONT', 'ALGO', 'ADA', 'BTC', 'FXS', 'GALA', 'BONK', 'LUNA', 'XRP', 'ADA', 'MANA', 'TRX', 'BTC', 'OMG', 'GRT', 'BICO', 'ICP', 'BAND', 'LDO', 'SATS', 'ZRX', 'QTUM', 'YFI', '1INCH', 'SOL', 'ETH', 'API3', 'DOT', 'ALPHA', 'DOGE', 'REN', 'USDC', 'LINK', 'WLD', 'LQTY', 'IOTA', 'TRB', 'RVN', 'WSM', 'XCH', 'ALGO', 'KSM', 'KSM', 'YFII', 'CFX', 'FRONT', 'UMA', 'FTM', 'AGIX', 'MOVR', 'BAL', 'TURBO', 'ORDI', 'MAGIC', 'PYTH', 'ANT', 'ETC', 'CTC', 'CRV', 'BIGTIME', 'ID', 'MATIC', 'THETA', 'RON', 'LTC', 'STORJ', 'IOST', 'BTC', 'BNB', 'RSR', 'KNC', 'ORBS', 'XLM', 'NMR', 'LINK', 'NFT', 'COMP', 'SOL', 'BADGER', 'THETA', 'GRT', 'DOT', 'FIL', 'JTO', 'TIA', 'ENS', 'BSV', 'GAS', 'OP', 'GFT', 'CORE', 'SUSHI', 'JST', 'LTC', 'WAXP', 'FET', 'TON', 'ETHW', 'ATOM', 'TRX', 'SSV', 'ETC', 'SAND', 'CELO', 'KLAY', 'LOOKS', 'EOS', '1INCH', 'MANA', 'SWEAT', 'AR', 'FLOW', 'CSPR', 'CEL', 'ETH', 'ATOM', 'STARL', 'NEO', 'AIDOGE', 'BAT', 'WOO', 'PEOPLE', 'GMT', 'ZIL', 'MASK', 'BCH', 'GAL', 'NEAR', 'RACA', 'FITFI', 'HBAR', 'XRP', 'BNT', 'BSV', 'RDNT', 'AXS']

# Create the XML string
xml_string = '<string-array name="planets_only">\n'
for coin in coin_list:
    xml_string += f'    <item>{coin}</item>\n'
xml_string += '</string-array>'

# Print or save the XML string
print(xml_string)
