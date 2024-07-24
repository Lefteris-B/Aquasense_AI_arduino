import { defineConfig } from "vite"
import { ViteImageOptimizer } from 'vite-plugin-image-optimizer';
import { viteSingleFile } from "vite-plugin-singlefile"


export default defineConfig({
    plugins: [ViteImageOptimizer()]
})
