#!/bin/bash
echo url="https://www.duckdns.org/update?domains=legacychurchhvac&token=6bbe9764-1930-42da-9256-0987ef59c2c2&ip=" | curl -k -o ~/duckdns/duck.log -K -
