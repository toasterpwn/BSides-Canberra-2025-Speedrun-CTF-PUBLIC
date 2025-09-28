FROM node:22-bookworm

COPY flag-submit/package.json /app/package.json
WORKDIR /app
RUN npm install
COPY flag-submit/index.js /app/index.js
COPY flag-submit/start.sh /app/start.sh
RUN chmod +x /app/start.sh

USER node
CMD ["/app/start.sh"]