FROM debian:12

RUN apt update \
  && apt install -y \
  sqlite3 build-essential time curl cmake git nano dos2unix \
  && apt clean \
  && /bin/rm -rf /var/lib/apt/lists/*

WORKDIR /app

CMD bash -i
