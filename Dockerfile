FROM debian:bookworm
WORKDIR /image_linux


RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    python3-venv \
    wget \
    git \
    procps \
    nmap \
    curl \
    unzip \
    libpcap-dev \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Создаем симлинк python3 -> python
RUN ln -sf /usr/bin/python3 /usr/bin/python

# Создаем виртуальное окружение и устанавливаем зависимости
RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"



RUN wget https://go.dev/dl/go1.24.7.linux-amd64.tar.gz -O /tmp/go.tar.gz && \
    tar -C /usr/local -xzf /tmp/go.tar.gz && \
    rm /tmp/go.tar.gz

ENV PATH="/usr/local/go/bin:/root/go/bin:${PATH}"
ENV GOPATH="/root/go"
ENV CGO_ENABLED=1

# Создаем директорию для Go
RUN mkdir -p /root/go

RUN go install -v github.com/projectdiscovery/dnsx/cmd/dnsx@latest

RUN /opt/venv/bin/pip install --no-cache-dir dnsgen



# Устанавливаем инструменты
RUN go install github.com/owasp-amass/amass/v3/...@latest
RUN go install github.com/d3mondev/puredns/v2@latest

# Устанавливаем инструменты ProjectDiscovery с совместимыми версиями
RUN go install -v github.com/projectdiscovery/naabu/v2/cmd/naabu@v2.3.4
RUN go install -v github.com/projectdiscovery/nuclei/v2/cmd/nuclei@latest
RUN go install -v github.com/projectdiscovery/httpx/cmd/httpx@latest
RUN go install -v github.com/projectdiscovery/subfinder/v2/cmd/subfinder@latest


CMD ["bash"]